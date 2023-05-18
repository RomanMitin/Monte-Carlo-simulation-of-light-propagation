using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Web;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

using System.Text.Json;
using System.IO;
using System.Xml.Linq;
using static System.Windows.Forms.AxHost;

namespace Photon_propagation_frontend
{
    public enum launch_param
    {
        simulation = 1, visalizer = 2
    }


    public partial class Photon_prapagation_form : Form
    {

        public State_t state { get; set; }
        bool enableLayersTableEvents;

        public Photon_prapagation_form()
        {
            enableLayersTableEvents = true;
            System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");

            InitializeComponent();
            LayersTable[0, 0].Value = "1";

            InitState();
        }

        public void InitState()
        {
            state = new State_t();
            state.layers = new List<Layer_t> { new Layer_t() };

            state.Photon_num = Convert.ToUInt64(numPhotonNum.Value);
            state.Thread_num = Convert.ToUInt32(numThreadNum.Value);
            state.Critical_weight = Convert.ToDouble(CriticalWeihtTextBox.Text);

            state.dr = Convert.ToDouble(drTextBox.Text);
            state.dz = Convert.ToDouble(dzTextBox.Text);
            state.lenght_r = Convert.ToDouble(Lenght_rTextBox.Text);

        }

        public void TryGetNumber(string in_number, out double out_number)
        {
            if (!double.TryParse(in_number, out out_number))
            {
                MessageBox.Show("Wrong number format, try again",
                    "Error",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error,
                    MessageBoxDefaultButton.Button1);
            }
        }

        public string GetFileName(bool show_json)
        {
            if (show_json)
            {
                FileDialog.Filter = "Json files (*.json)|*.json";
            }
            else
            {
                FileDialog.Filter = "Bin files(*.bin)|*.bin|All files(*.*)|*.*";

            }
            if (FileDialog.ShowDialog() == DialogResult.Cancel)
                return null;
            return FileDialog.FileName;
        }

        // EVENTS HANDLE CODE ----------------------------------------------

        private void numThreadNum_ValueChanged(object sender, EventArgs e)
        {
            state.Thread_num = Convert.ToUInt32(numThreadNum.Value);
        }

        private void numPhotonNum_ValueChanged(object sender, EventArgs e)
        {
            state.Photon_num = Convert.ToUInt64(numPhotonNum.Value);
        }

        private void CriticalWeihtTextBox_TextChanged(object sender, EventArgs e)
        {
            double tmp;
            TryGetNumber(CriticalWeihtTextBox.Text, out tmp);

            if (tmp <= 0 || tmp > 1)
            {
                MessageBox.Show("Critical weight must be at least 0.0 and at most 1.0, try again",
                    "Error",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error,
                    MessageBoxDefaultButton.Button1);
            }

            state.Critical_weight = tmp;
        }

        private void drTextBox_TextChanged(object sender, EventArgs e)
        {
            double tmp;
            TryGetNumber(drTextBox.Text, out tmp);
            state.dr = tmp;
        }

        private void dzTextBox_TextChanged(object sender, EventArgs e)
        {
            double tmp;
            TryGetNumber(dzTextBox.Text, out tmp);
            state.dz = tmp;
        }

        private void Lenght_rTextBox_TextChanged(object sender, EventArgs e)
        {
            double tmp;
            TryGetNumber(Lenght_rTextBox.Text, out tmp);
            state.lenght_r = tmp;
        }

        public void updateFormData()
        {
            numThreadNum.Value = state.Thread_num;
            numPhotonNum.Value = state.Photon_num;
            CriticalWeihtTextBox.Text = state.Critical_weight.ToString();

            drTextBox.Text = state.dr.ToString();
            dzTextBox.Text = state.dz.ToString();
            Lenght_rTextBox.Text = state.lenght_r.ToString();

            enableLayersTableEvents = false;
            LayersTable.Rows.Clear();
            int i = 0;
            for (i = 0; i < state.layers.Count; i++)
            {
                Layer_t layer = state.layers[i];
                LayersTable.Rows.Add(i + 1,
                    layer.n.ToString(),
                    layer.z1.ToString(),
                    layer.mua.ToString(),
                    layer.mus.ToString(),
                    layer.g.ToString());
            }
            LayersTable[0, LayersTable.Rows.Count - 1].Value = i + 1;
            state.layers.Add(new Layer_t());
            enableLayersTableEvents = true;
        }

        private void InputFileButton_Click(object sender, EventArgs e)
        {
            if (InputFileTextBox.Text != string.Empty)
            {
                SerializeState(InputFileTextBox.Text);
            }

            string filename = GetFileName(true);
            if (filename != null)
            {
                InputFileTextBox.Text = filename;
                if(File.Exists(filename))
                {
                    DeserializeState(filename);
                    updateFormData();
                }
                else
                {
                    SerializeState(filename);
                }
            }
        }

        private void OutputFileButton_Click(object sender, EventArgs e)
        {
            OutputFileTextBox.Text = GetFileName(false) ?? OutputFileTextBox.Text;
        }


        public void PrepareStateForSerialize()
        {
            List<Layer_t> layers = state.layers;

            Debug.Assert(double.IsNaN(layers[layers.Count - 1].z0) &&
                double.IsNaN(layers[layers.Count - 1].z1) &&
                double.IsNaN(layers[layers.Count - 1].n) &&
                 double.IsNaN(layers[layers.Count - 1].mua));

            layers.RemoveAt(layers.Count - 1);

            if (layers.Count > 0)
            {
                layers[0].z0 = 0;
                for (int i = 0; i < layers.Count - 1; i++)
                {
                    layers[i + 1].z0 = layers[i].z1;
                }
            }
        }

        public bool CheckForNanInLayers()
        {
            foreach (var layer in state.layers)
            {
                if (layer.n == double.NaN ||
                   layer.z0 == double.NaN ||
                   layer.z1 == double.NaN ||
                   layer.mua == double.NaN ||
                   layer.mus == double.NaN ||
                   layer.g == double.NaN)
                {
                    MessageBox.Show("Fill all cells in Layers Setting and try again!",
                        "Not enoght data",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error);
                    return false;
                }
            }

            return true;
        }

        public bool CheckInputBeforeStart(int launch_flags)
        {
            bool result = true;
            if ((launch_flags & (int)launch_param.simulation) != 0)
                result &= CheckForNanInLayers() && InputFileTextBox.Text.Length > 0;

            result &= CheckForNanInLayers() && OutputFileTextBox.Text.Length > 0;

            return result;
        }

        public void SerializeState(string filename)
        {
            PrepareStateForSerialize();


            if (!CheckForNanInLayers())
            {
                state.layers.Add(new Layer_t());
                return;
            }

            var options = new JsonSerializerOptions
            {
                WriteIndented = true
            };
            string json = JsonSerializer.Serialize(state, options);
            json = "{\n\"State\": \n" + json + "\n}";
            File.WriteAllText(filename, json);

            state.layers.Add(new Layer_t());
        }

        public void DeserializeState(string filename)
        {
            string json_file= File.ReadAllText(filename);
            var json_doc = JsonDocument.Parse(json_file);
            var state_json = json_doc.RootElement.EnumerateObject().First();

            state = JsonSerializer.Deserialize<State_t>(state_json.Value.ToString());
        }

        private void LayersTable_CellLeave(object sender, DataGridViewCellEventArgs e)
        {
            if (enableLayersTableEvents)
            {
                var Cell = LayersTable[e.ColumnIndex, e.RowIndex];
                if (Cell.EditedFormattedValue.ToString() != string.Empty)
                {
                    double value;
                    TryGetNumber(Cell.EditedFormattedValue.ToString(), out value);
                    switch ((Layer_t.ID)e.ColumnIndex)
                    {
                        case Layer_t.ID.idn:
                            state.layers[e.RowIndex].n = value;
                            break;
                        case Layer_t.ID.idz1:
                            state.layers[e.RowIndex].z1 = value;
                            break;
                        case Layer_t.ID.idmua:
                            state.layers[e.RowIndex].mua = value;
                            break;
                        case Layer_t.ID.idmus:
                            state.layers[e.RowIndex].mus = value;
                            break;
                        case Layer_t.ID.idg:
                            state.layers[e.RowIndex].g = value;
                            break;
                        default:
                            return;
                    }
                }
            }
        }

        private void LayersTable_RowsAdded(object sender, DataGridViewRowsAddedEventArgs e)
        {
            if (enableLayersTableEvents)
            {
                var Cell = LayersTable[0, e.RowIndex];
                Cell.Value = (e.RowIndex + 1).ToString();
                state.layers.Add(new Layer_t());
            }
        }

        public void showInputFileMissingError()
        {
            MessageBox.Show("Select input file to save data", 
                "Missing input file",
                MessageBoxButtons.OK, 
                MessageBoxIcon.Error);
        }

        private void SaveButton_Click(object sender, EventArgs e)
        {
            if(InputFileTextBox.Text.Length > 0) 
            {
                SerializeState(InputFileTextBox.Text);
            }
            else
            {
                showInputFileMissingError();
            }
        }

        private void launch_sim_form(int flags)
        {
            if (CheckInputBeforeStart(flags))
            {
                if((flags & (int)launch_param.simulation) != 0)
                    SerializeState(InputFileTextBox.Text);

                SimulationForm simform = new SimulationForm(InputFileTextBox.Text,
                    OutputFileTextBox.Text, (int)numPhotonNum.Value,
                        flags);
            }
            else
            {
                MessageBox.Show("Fill all necessary fields in input forms",
                "Missing input data",
                MessageBoxButtons.OK,
                MessageBoxIcon.Error);
            }
        }

        private void StartButton_Click(object sender, EventArgs e)
        {
            launch_sim_form((int)launch_param.visalizer + (int)launch_param.simulation);
        }

        private void VisualizeButton_Click(object sender, EventArgs e)
        {
            launch_sim_form((int)launch_param.visalizer);
        }

        private void SimulateButton_Click(object sender, EventArgs e)
        {
            launch_sim_form((int)launch_param.simulation);
        }
    }
}
