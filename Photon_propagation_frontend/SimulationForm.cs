using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Photon_propagation_frontend
{
    public partial class SimulationForm : Form
    {
        public string InputFilename;
        public string OutputFilename;

        int launch_flags = 0;

        const Int32 PhotonNumReduction = (1 << 11);

        const string PathToBackendProcess = "..\\..\\..\\build\\Photon_propagation_backend\\Release\\Photon_propagation_backend.exe";

        public SimulationForm(string inputFilename, string outputFilename, Int32 Total_photon_num, int flags)
        {
            InitializeComponent();

            Show();

            InputFilename = inputFilename;
            OutputFilename = outputFilename;
            launch_flags = flags;


            if((launch_flags & (int)launch_param.simulation) != 0)
            {
                progressBar.Maximum = Total_photon_num / PhotonNumReduction;

                StartSimulation();
            }
            else
            {
                backgroundWorker1.DoWork += BackendProcess_Exited;
                backgroundWorker1.RunWorkerAsync();
            }
        }

        private void StartSimulation()
        {
            if(!File.Exists(PathToBackendProcess))
            {
                MessageBox.Show("Theire is no executable in " + PathToBackendProcess +
                    ". Build backend project with cmake to build folder before start simulation", "No backend executable",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            var processStartInfo = new ProcessStartInfo
            {
                FileName = PathToBackendProcess,
                Arguments = InputFilename + " " + OutputFilename,
                CreateNoWindow = true,
                RedirectStandardOutput = true,
                RedirectStandardError = true,
                UseShellExecute = false
            };
            
            BackendProcess = Process.Start(processStartInfo);
            BackendProcess.EnableRaisingEvents = true;
            BackendProcess.OutputDataReceived += new System.Diagnostics.DataReceivedEventHandler(BackendProcess_OutputDataReceived);
            BackendProcess.Exited += new System.EventHandler(BackendProcess_Exited);
            BackendProcess.BeginOutputReadLine();
        }

        delegate void void_int_delegate(int val);
        private void BackendProcess_OutputDataReceived(object sender, DataReceivedEventArgs e)
        {
            string NewPhotonNumStr = e.Data;
            if (e.Data != null)
            {
                Int32 NewPhotonNum = Int32.Parse(e.Data);

                BeginInvoke(new void_int_delegate(ChangeProgressBarValue),
                    NewPhotonNum / PhotonNumReduction);
            }
        }

        private void ChangeProgressBarValue(int NewVal)
        {
            progressBar.Value = NewVal;
        }

        delegate void void_image_delegate(Image img);
        delegate void void_void_delegate();
        private void BackendProcess_Exited(object sender, EventArgs e)
        {
            BeginInvoke(new void_int_delegate(ChangeProgressBarValue),
                    progressBar.Maximum);
            if ((launch_flags & (int)launch_param.visalizer) != 0)
            {
                /*MessageBox.Show("Simulation end with exit code: " + BackendProcess.ExitCode);*/
                double[,] Matrix = InputBinFile.GetMatrixFromFile(OutputFilename);

                Image img = Visualizer.GetImage(Matrix);

                BeginInvoke(new void_image_delegate(UpdatePictureBox), img);
            }
            else
            {
                MessageBox.Show("Simulation complited\n",
                                "Simulation",
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Information);
                BeginInvoke(new void_void_delegate(Close));
            }
            
        }

        private void UpdatePictureBox(Image img)
        {
            pictureBox1.Width = img.Width; 
            pictureBox1.Height = img.Height;
            pictureBox1.Image = img;
            pictureBox1.Refresh();
        }
    }
}
