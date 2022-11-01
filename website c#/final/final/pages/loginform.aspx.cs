using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;

namespace final.pages
{
    public partial class loginform : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }
        SqlConnection con = new SqlConnection(@"Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=|DataDirectory|\Database1.mdf;Integrated Security=True");
        SqlCommand com = new SqlCommand();
        DataSet1 data = new DataSet1();

        protected void butOk_Click(object sender, EventArgs e)
        {
            try
            {
                com.CommandText = "Select * From Items where login= '" + loginlogin.Text + "' and password='" + password.Text + "'";
                com.Connection = con;
                con.Open();
                SqlDataAdapter adp = new SqlDataAdapter(com.CommandText, con);
                adp.Fill(data, "Items");
                var rowCount = data.Tables["Items"].Rows.Count;
                if (rowCount > 0)
                {
                    
                    Label1.Text = "Welcome!";
                    Session["loginses"] = loginlogin.Text;
                    loginlogin.Text = "";
                    password.Text = "";
                }
                else
                {

                    loginlogin.Text = "";
                    password.Text = "";
                    Label1.Text = "Sorry, wrong login or password...";
                }
            }
            finally
            {
                con.Close();
            }
        }

        protected void butCanc_Click(object sender, EventArgs e)
        {
            Response.Redirect("finalsite.aspx");
        }
    }
}