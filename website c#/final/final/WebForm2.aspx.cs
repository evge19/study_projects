using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.IO;
using System.Data.SqlClient;

namespace final
{
    public partial class WebForm2 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["loginses"] != null)
            {
                Labellogin.Text = Session["loginses"].ToString();
            }
            Label2.Text = "";
        }
        SqlConnection con = new SqlConnection(@"Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=|DataDirectory|\Database1.mdf;Integrated Security=True");
        SqlCommand com = new SqlCommand();
        DataSet3 data = new DataSet3();
        protected void Button1_Click(object sender, EventArgs e)
        {
            string filenamed = "";
            if (FileUpload1.HasFile)
            {
                filenamed = "files/" + Path.GetFileName(FileUpload1.FileName);
                FileUpload1.SaveAs(Server.MapPath(filenamed));
            }
            if (!Page.IsValid) return;
            {
                
                com.CommandText = "";
                SqlDataAdapter adp = new SqlDataAdapter(com.CommandText, con);
                Random rnd = new Random();
                data.EnforceConstraints = false;
                try
                {
                    com.CommandText = "Insert Into Requesttable (email, request,filepath) values ('" + TextBox2.Text + "','" + TextBox1.Text + "','" + filenamed + "')";
                    com.Connection = con;
                    con.Open();
                    com.ExecuteNonQuery();
                    TextBox1.Text = "";
                    TextBox2.Text = "";
                    filenamed = "";
                }
                finally
                {
                    con.Close();
                }
                Label2.Text = "Request sent";
                TextBox1.Text = "";
                TextBox2.Text = "";
            }
                
        }

        protected void Butsignout_Click(object sender, EventArgs e)
        {
            Session.Clear();
        }
    }
}