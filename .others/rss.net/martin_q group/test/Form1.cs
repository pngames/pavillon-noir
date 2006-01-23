using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using test.nrss;

namespace test
{
  public partial class Form1 : Form
  {
	test.nrss.Service serviceAdd = new test.nrss.Service();

	public Form1()
	{
	  InitializeComponent();
	}

	private void button1_Click(object sender, EventArgs e)
	{
	  User user = new User();

	  user.Email = this.t_user.Text;
	  user.Passwd = this.t_pass.Text;

	  //this.t_hash.Text = serviceAdd.createUser(user);
	  //serviceAdd.validateUser(this.t_hash.Text);
	  user = serviceAdd.logon(this.t_user.Text, this.t_pass.Text);

	  this.t_user.Text = user.Email;
	  this.t_pass.Text = user.Passwd;
	  this.t_id.Text = user.Id.ToString();
	}
  }
}