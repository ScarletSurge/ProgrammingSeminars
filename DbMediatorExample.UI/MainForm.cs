using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

using DbMediatorExample.Database;
using DbMediatorExample.Database.Models;

namespace DbMediatorExample.UI
{

    public partial class MainForm : Form
    {

        private IEnumerable<Region> _regions;
        private DatabaseMediator _mediator;

        public MainForm()
        {
            InitializeComponent();
            _mediator = new DatabaseMediator();
        }

        private async void Form1_Load(object sender, EventArgs e)
        {
            _regions = await _mediator.GetRegionsAsync();
            regionsComboBox.DataSource = _regions;
            regionsComboBox.DisplayMember = "Name";
        }

        private async void regionsComboBox_SelectedValueChanged(object sender, EventArgs e)
        {
            var result = default(IEnumerable<Target>);
            try
            {
                regionsComboBox.Enabled = false;
                result = await _mediator.GetTargetsAsync((regionsComboBox.SelectedItem as Region).Id);
            }
            catch (Exception)
            {
                MessageBox.Show("An unhandled exception occured!11!1");
            }
            finally
            {
                regionsComboBox.Enabled = true;
            }

            usersDataGridView.Rows.Clear();
            foreach (var resultItem in result ?? Enumerable.Empty<Target>())
            {
                var rowId = usersDataGridView.Rows.Add();
                usersDataGridView.Rows[rowId].Cells["id"].Value = resultItem.Id;
                usersDataGridView.Rows[rowId].Cells["login"].Value = resultItem.Login;
                usersDataGridView.Rows[rowId].Cells["name"].Value = resultItem.Name;
                usersDataGridView.Rows[rowId].Cells["surname"].Value = resultItem.Surname;
                usersDataGridView.Rows[rowId].Cells["birthDate"].Value = resultItem.BirthDate;
                usersDataGridView.Rows[rowId].Cells["region"].Value = resultItem.Region;
            }
        }
    }

}