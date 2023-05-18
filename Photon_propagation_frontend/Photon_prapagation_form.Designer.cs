namespace Photon_propagation_frontend
{
    partial class Photon_prapagation_form
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.lblHelloWorld = new System.Windows.Forms.Label();
            this.numThreadNum = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.numPhotonNum = new System.Windows.Forms.NumericUpDown();
            this.AbsorbingGridParam = new System.Windows.Forms.GroupBox();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.Lenght_rTextBox = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.dzTextBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.drTextBox = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.InputFileTextBox = new System.Windows.Forms.TextBox();
            this.OutputFileTextBox = new System.Windows.Forms.TextBox();
            this.InputFileButton = new System.Windows.Forms.Button();
            this.OutputFileButton = new System.Windows.Forms.Button();
            this.FileDialog = new System.Windows.Forms.OpenFileDialog();
            this.label8 = new System.Windows.Forms.Label();
            this.LayersPanel = new System.Windows.Forms.Panel();
            this.LayersTable = new System.Windows.Forms.DataGridView();
            this.number = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.n = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.z1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.mua = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.mus = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.g = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.SaveButton = new System.Windows.Forms.Button();
            this.StartButton = new System.Windows.Forms.Button();
            this.label9 = new System.Windows.Forms.Label();
            this.CriticalWeihtTextBox = new System.Windows.Forms.TextBox();
            this.VisualizeButton = new System.Windows.Forms.Button();
            this.SimulateButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.numThreadNum)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numPhotonNum)).BeginInit();
            this.AbsorbingGridParam.SuspendLayout();
            this.LayersPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.LayersTable)).BeginInit();
            this.SuspendLayout();
            // 
            // lblHelloWorld
            // 
            this.lblHelloWorld.AutoSize = true;
            this.lblHelloWorld.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblHelloWorld.Location = new System.Drawing.Point(12, 9);
            this.lblHelloWorld.Name = "lblHelloWorld";
            this.lblHelloWorld.Size = new System.Drawing.Size(183, 24);
            this.lblHelloWorld.TabIndex = 1;
            this.lblHelloWorld.Text = "Number of threads";
            // 
            // numThreadNum
            // 
            this.numThreadNum.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.numThreadNum.Location = new System.Drawing.Point(16, 51);
            this.numThreadNum.Maximum = new decimal(new int[] {
            4096,
            0,
            0,
            0});
            this.numThreadNum.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numThreadNum.Name = "numThreadNum";
            this.numThreadNum.Size = new System.Drawing.Size(120, 24);
            this.numThreadNum.TabIndex = 2;
            this.numThreadNum.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numThreadNum.ValueChanged += new System.EventHandler(this.numThreadNum_ValueChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(12, 94);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(189, 24);
            this.label1.TabIndex = 3;
            this.label1.Text = "Number of photons";
            // 
            // numPhotonNum
            // 
            this.numPhotonNum.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.numPhotonNum.Increment = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numPhotonNum.Location = new System.Drawing.Point(16, 141);
            this.numPhotonNum.Maximum = new decimal(new int[] {
            1000000000,
            0,
            0,
            0});
            this.numPhotonNum.Name = "numPhotonNum";
            this.numPhotonNum.Size = new System.Drawing.Size(120, 24);
            this.numPhotonNum.TabIndex = 4;
            this.numPhotonNum.Value = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numPhotonNum.ValueChanged += new System.EventHandler(this.numPhotonNum_ValueChanged);
            // 
            // AbsorbingGridParam
            // 
            this.AbsorbingGridParam.Controls.Add(this.textBox4);
            this.AbsorbingGridParam.Controls.Add(this.label5);
            this.AbsorbingGridParam.Controls.Add(this.label4);
            this.AbsorbingGridParam.Controls.Add(this.Lenght_rTextBox);
            this.AbsorbingGridParam.Controls.Add(this.label3);
            this.AbsorbingGridParam.Controls.Add(this.dzTextBox);
            this.AbsorbingGridParam.Controls.Add(this.label2);
            this.AbsorbingGridParam.Controls.Add(this.drTextBox);
            this.AbsorbingGridParam.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.AbsorbingGridParam.Location = new System.Drawing.Point(222, 9);
            this.AbsorbingGridParam.Name = "AbsorbingGridParam";
            this.AbsorbingGridParam.Size = new System.Drawing.Size(241, 198);
            this.AbsorbingGridParam.TabIndex = 5;
            this.AbsorbingGridParam.TabStop = false;
            this.AbsorbingGridParam.Text = "Absorbing grid size and density ";
            // 
            // textBox4
            // 
            this.textBox4.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox4.Location = new System.Drawing.Point(144, 146);
            this.textBox4.Multiline = true;
            this.textBox4.Name = "textBox4";
            this.textBox4.ReadOnly = true;
            this.textBox4.Size = new System.Drawing.Size(91, 46);
            this.textBox4.TabIndex = 14;
            this.textBox4.Text = "Set in layers settings";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(6, 160);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(144, 16);
            this.label5.TabIndex = 13;
            this.label5.Text = "Lenght by z coordinate:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(6, 113);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(142, 16);
            this.label4.TabIndex = 12;
            this.label4.Text = "Lenght by r coordinate:";
            // 
            // Lenght_rTextBox
            // 
            this.Lenght_rTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Lenght_rTextBox.Location = new System.Drawing.Point(159, 109);
            this.Lenght_rTextBox.Name = "Lenght_rTextBox";
            this.Lenght_rTextBox.Size = new System.Drawing.Size(76, 24);
            this.Lenght_rTextBox.TabIndex = 11;
            this.Lenght_rTextBox.Text = "10.0";
            this.Lenght_rTextBox.Validated += new System.EventHandler(this.Lenght_rTextBox_TextChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(6, 70);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(149, 32);
            this.label3.TabIndex = 10;
            this.label3.Text = "Density by z coordinate:\r\nΔz";
            // 
            // dzTextBox
            // 
            this.dzTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.dzTextBox.Location = new System.Drawing.Point(159, 70);
            this.dzTextBox.Name = "dzTextBox";
            this.dzTextBox.Size = new System.Drawing.Size(76, 24);
            this.dzTextBox.TabIndex = 9;
            this.dzTextBox.Text = "0.5";
            this.dzTextBox.Validated += new System.EventHandler(this.dzTextBox_TextChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(6, 37);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(147, 32);
            this.label2.TabIndex = 8;
            this.label2.Text = "Density by r coordinate:\r\nΔr";
            // 
            // drTextBox
            // 
            this.drTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.drTextBox.Location = new System.Drawing.Point(159, 37);
            this.drTextBox.Name = "drTextBox";
            this.drTextBox.Size = new System.Drawing.Size(76, 24);
            this.drTextBox.TabIndex = 0;
            this.drTextBox.Text = "0.5\r\n";
            this.drTextBox.Validated += new System.EventHandler(this.drTextBox_TextChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.BackColor = System.Drawing.SystemColors.ButtonShadow;
            this.label6.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(15, 277);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(143, 26);
            this.label6.TabIndex = 8;
            this.label6.Text = "Input file path:";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.BackColor = System.Drawing.SystemColors.ButtonShadow;
            this.label7.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(15, 418);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(159, 26);
            this.label7.TabIndex = 9;
            this.label7.Text = "Output file path:";
            // 
            // InputFileTextBox
            // 
            this.InputFileTextBox.Location = new System.Drawing.Point(15, 309);
            this.InputFileTextBox.Multiline = true;
            this.InputFileTextBox.Name = "InputFileTextBox";
            this.InputFileTextBox.ReadOnly = true;
            this.InputFileTextBox.Size = new System.Drawing.Size(210, 42);
            this.InputFileTextBox.TabIndex = 10;
            // 
            // OutputFileTextBox
            // 
            this.OutputFileTextBox.Location = new System.Drawing.Point(15, 450);
            this.OutputFileTextBox.Multiline = true;
            this.OutputFileTextBox.Name = "OutputFileTextBox";
            this.OutputFileTextBox.ReadOnly = true;
            this.OutputFileTextBox.Size = new System.Drawing.Size(210, 45);
            this.OutputFileTextBox.TabIndex = 11;
            // 
            // InputFileButton
            // 
            this.InputFileButton.Location = new System.Drawing.Point(231, 309);
            this.InputFileButton.Name = "InputFileButton";
            this.InputFileButton.Size = new System.Drawing.Size(75, 23);
            this.InputFileButton.TabIndex = 12;
            this.InputFileButton.Text = "Browse";
            this.InputFileButton.UseVisualStyleBackColor = true;
            this.InputFileButton.Click += new System.EventHandler(this.InputFileButton_Click);
            // 
            // OutputFileButton
            // 
            this.OutputFileButton.Location = new System.Drawing.Point(231, 450);
            this.OutputFileButton.Name = "OutputFileButton";
            this.OutputFileButton.Size = new System.Drawing.Size(75, 23);
            this.OutputFileButton.TabIndex = 13;
            this.OutputFileButton.Text = "Browse";
            this.OutputFileButton.UseVisualStyleBackColor = true;
            this.OutputFileButton.Click += new System.EventHandler(this.OutputFileButton_Click);
            // 
            // FileDialog
            // 
            this.FileDialog.CheckFileExists = false;
            this.FileDialog.FileName = "openFileDialog1";
            this.FileDialog.Title = "Choose file";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(75, 15);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(138, 24);
            this.label8.TabIndex = 16;
            this.label8.Text = "Layers setting";
            // 
            // LayersPanel
            // 
            this.LayersPanel.Controls.Add(this.LayersTable);
            this.LayersPanel.Controls.Add(this.label8);
            this.LayersPanel.Location = new System.Drawing.Point(469, 9);
            this.LayersPanel.Name = "LayersPanel";
            this.LayersPanel.Size = new System.Drawing.Size(317, 419);
            this.LayersPanel.TabIndex = 15;
            // 
            // LayersTable
            // 
            this.LayersTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.LayersTable.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.number,
            this.n,
            this.z1,
            this.mua,
            this.mus,
            this.g});
            this.LayersTable.Location = new System.Drawing.Point(13, 42);
            this.LayersTable.Name = "LayersTable";
            this.LayersTable.Size = new System.Drawing.Size(283, 352);
            this.LayersTable.TabIndex = 17;
            this.LayersTable.CellLeave += new System.Windows.Forms.DataGridViewCellEventHandler(this.LayersTable_CellLeave);
            this.LayersTable.RowsAdded += new System.Windows.Forms.DataGridViewRowsAddedEventHandler(this.LayersTable_RowsAdded);
            // 
            // number
            // 
            this.number.HeaderText = "№";
            this.number.Name = "number";
            this.number.ReadOnly = true;
            this.number.Width = 40;
            // 
            // n
            // 
            this.n.HeaderText = "n";
            this.n.Name = "n";
            this.n.Width = 40;
            // 
            // z1
            // 
            this.z1.HeaderText = "z1";
            this.z1.Name = "z1";
            this.z1.Width = 40;
            // 
            // mua
            // 
            this.mua.HeaderText = "mua";
            this.mua.Name = "mua";
            this.mua.Width = 40;
            // 
            // mus
            // 
            this.mus.HeaderText = "mus";
            this.mus.Name = "mus";
            this.mus.Width = 40;
            // 
            // g
            // 
            this.g.HeaderText = "g";
            this.g.Name = "g";
            this.g.Width = 40;
            // 
            // SaveButton
            // 
            this.SaveButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SaveButton.Location = new System.Drawing.Point(231, 338);
            this.SaveButton.Name = "SaveButton";
            this.SaveButton.Size = new System.Drawing.Size(75, 23);
            this.SaveButton.TabIndex = 18;
            this.SaveButton.Text = "Save";
            this.SaveButton.UseVisualStyleBackColor = true;
            this.SaveButton.Click += new System.EventHandler(this.SaveButton_Click);
            // 
            // StartButton
            // 
            this.StartButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.StartButton.Location = new System.Drawing.Point(366, 450);
            this.StartButton.Name = "StartButton";
            this.StartButton.Size = new System.Drawing.Size(145, 97);
            this.StartButton.TabIndex = 19;
            this.StartButton.Text = "Simulate and visualize";
            this.StartButton.UseVisualStyleBackColor = true;
            this.StartButton.Click += new System.EventHandler(this.StartButton_Click);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.Location = new System.Drawing.Point(12, 177);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(140, 24);
            this.label9.TabIndex = 20;
            this.label9.Text = "Critical weight";
            // 
            // CriticalWeihtTextBox
            // 
            this.CriticalWeihtTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CriticalWeihtTextBox.Location = new System.Drawing.Point(16, 218);
            this.CriticalWeihtTextBox.Name = "CriticalWeihtTextBox";
            this.CriticalWeihtTextBox.Size = new System.Drawing.Size(120, 24);
            this.CriticalWeihtTextBox.TabIndex = 21;
            this.CriticalWeihtTextBox.Text = "0.3";
            this.CriticalWeihtTextBox.Validated += new System.EventHandler(this.CriticalWeihtTextBox_TextChanged);
            // 
            // VisualizeButton
            // 
            this.VisualizeButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.VisualizeButton.Location = new System.Drawing.Point(517, 483);
            this.VisualizeButton.Name = "VisualizeButton";
            this.VisualizeButton.Size = new System.Drawing.Size(99, 40);
            this.VisualizeButton.TabIndex = 22;
            this.VisualizeButton.Text = "Visualize";
            this.VisualizeButton.UseVisualStyleBackColor = true;
            this.VisualizeButton.Click += new System.EventHandler(this.VisualizeButton_Click);
            // 
            // SimulateButton
            // 
            this.SimulateButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SimulateButton.Location = new System.Drawing.Point(261, 483);
            this.SimulateButton.Name = "SimulateButton";
            this.SimulateButton.Size = new System.Drawing.Size(99, 40);
            this.SimulateButton.TabIndex = 23;
            this.SimulateButton.Text = "Simulate";
            this.SimulateButton.UseVisualStyleBackColor = true;
            this.SimulateButton.Click += new System.EventHandler(this.SimulateButton_Click);
            // 
            // Photon_prapagation_form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(850, 559);
            this.Controls.Add(this.SimulateButton);
            this.Controls.Add(this.VisualizeButton);
            this.Controls.Add(this.CriticalWeihtTextBox);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.StartButton);
            this.Controls.Add(this.SaveButton);
            this.Controls.Add(this.LayersPanel);
            this.Controls.Add(this.OutputFileButton);
            this.Controls.Add(this.InputFileButton);
            this.Controls.Add(this.OutputFileTextBox);
            this.Controls.Add(this.InputFileTextBox);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.AbsorbingGridParam);
            this.Controls.Add(this.numPhotonNum);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.numThreadNum);
            this.Controls.Add(this.lblHelloWorld);
            this.Name = "Photon_prapagation_form";
            this.Text = "Photon_prapagation";
            ((System.ComponentModel.ISupportInitialize)(this.numThreadNum)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numPhotonNum)).EndInit();
            this.AbsorbingGridParam.ResumeLayout(false);
            this.AbsorbingGridParam.PerformLayout();
            this.LayersPanel.ResumeLayout(false);
            this.LayersPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.LayersTable)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblHelloWorld;
        private System.Windows.Forms.NumericUpDown numThreadNum;
        private System.Windows.Forms.NumericUpDown numPhotonNum;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox AbsorbingGridParam;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox Lenght_rTextBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox dzTextBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox drTextBox;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button OutputFileButton;
        private System.Windows.Forms.Button InputFileButton;
        private System.Windows.Forms.TextBox OutputFileTextBox;
        private System.Windows.Forms.TextBox InputFileTextBox;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.OpenFileDialog FileDialog;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Panel LayersPanel;
        private System.Windows.Forms.DataGridView LayersTable;
        private System.Windows.Forms.DataGridViewTextBoxColumn number;
        private System.Windows.Forms.DataGridViewTextBoxColumn n;
        private System.Windows.Forms.DataGridViewTextBoxColumn z1;
        private System.Windows.Forms.DataGridViewTextBoxColumn mua;
        private System.Windows.Forms.DataGridViewTextBoxColumn mus;
        private System.Windows.Forms.DataGridViewTextBoxColumn g;
        private System.Windows.Forms.Button SaveButton;
        private System.Windows.Forms.Button StartButton;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox CriticalWeihtTextBox;
        private System.Windows.Forms.Button VisualizeButton;
        private System.Windows.Forms.Button SimulateButton;
    }
}

