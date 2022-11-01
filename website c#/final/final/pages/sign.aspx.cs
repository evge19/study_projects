using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;

namespace final.pages
{
    public partial class sign : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            string script = "return confirm(document.getElementById('up-name').value +' '+document.getElementById('up-lastname').value+', You are with us!');";
            butUp.Attributes.Add("onclick", script);
        }

        protected void butIn_Click(object sender, EventArgs e)
        {
            Response.Redirect("loginform.aspx");

        }

        protected void butCanc_Click(object sender, EventArgs e)
        {
            Response.Redirect("finalsite.aspx");

        }
        SqlConnection con = new SqlConnection(@"Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=|DataDirectory|\Database1.mdf;Integrated Security=True");
        SqlCommand com = new SqlCommand();
        DataSet1 data = new DataSet1();
        protected void butUp_Click(object sender, EventArgs e)
        {
            com.CommandText = "";
            SqlDataAdapter adp = new SqlDataAdapter(com.CommandText, con);
            Random rnd = new Random();
            data.EnforceConstraints = false;
            try
            {
                com.CommandText = "Insert Into Items (login, password) values ('" + loginsign.Text + "','" + passwordsign.Text + "')";
                com.Connection = con;
                con.Open();
                com.ExecuteNonQuery();
                loginsign.Text = "";
                passwordsign.Text = "";
            }
            finally
            {
                con.Close();
            }
        }
    }
}