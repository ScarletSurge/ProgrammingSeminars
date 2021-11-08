namespace DbMediatorExample.UI
{
    partial class MainForm
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
            this.usersDataGridView = new System.Windows.Forms.DataGridView();
            this.id = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.login = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.name = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.surname = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.birthDate = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.region = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.regionsComboBox = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this.usersDataGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // usersDataGridView
            // 
            this.usersDataGridView.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.usersDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.usersDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.id,
            this.login,
            this.name,
            this.surname,
            this.birthDate,
            this.region});
            this.usersDataGridView.Location = new System.Drawing.Point(228, 12);
            this.usersDataGridView.Name = "usersDataGridView";
            this.usersDataGridView.Size = new System.Drawing.Size(643, 423);
            this.usersDataGridView.TabIndex = 1;
            // 
            // id
            // 
            this.id.HeaderText = "Id";
            this.id.Name = "id";
            this.id.ReadOnly = true;
            // 
            // login
            // 
            this.login.HeaderText = "Login";
            this.login.Name = "login";
            this.login.ReadOnly = true;
            // 
            // name
            // 
            this.name.HeaderText = "Name";
            this.name.Name = "name";
            this.name.ReadOnly = true;
            // 
            // surname
            // 
            this.surname.HeaderText = "Surname";
            this.surname.Name = "surname";
            this.surname.ReadOnly = true;
            // 
            // birthDate
            // 
            this.birthDate.HeaderText = "BirthDate";
            this.birthDate.Name = "birthDate";
            this.birthDate.ReadOnly = true;
            // 
            // region
            // 
            this.region.HeaderText = "Region";
            this.region.Name = "region";
            this.region.ReadOnly = true;
            // 
            // regionsComboBox
            // 
            this.regionsComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.regionsComboBox.FormattingEnabled = true;
            this.regionsComboBox.Location = new System.Drawing.Point(12, 12);
            this.regionsComboBox.Name = "regionsComboBox";
            this.regionsComboBox.Size = new System.Drawing.Size(181, 21);
            this.regionsComboBox.TabIndex = 3;
            this.regionsComboBox.SelectedValueChanged += new System.EventHandler(this.regionsComboBox_SelectedValueChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(883, 450);
            this.Controls.Add(this.regionsComboBox);
            this.Controls.Add(this.usersDataGridView);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.usersDataGridView)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.DataGridView usersDataGridView;
        private System.Windows.Forms.ComboBox regionsComboBox;
        private System.Windows.Forms.DataGridViewTextBoxColumn id;
        private System.Windows.Forms.DataGridViewTextBoxColumn login;
        private System.Windows.Forms.DataGridViewTextBoxColumn name;
        private System.Windows.Forms.DataGridViewTextBoxColumn surname;
        private System.Windows.Forms.DataGridViewTextBoxColumn birthDate;
        private System.Windows.Forms.DataGridViewTextBoxColumn region;
    }
}

