using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Drawing;
using System.Data.SqlClient;
using System.Web.UI.HtmlControls;

namespace final.pages
{
    public partial class calendar : System.Web.UI.Page
    {
        public static List<string> pushedmonths = new List<string>();
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["loginses"] != null)
            {
                Labellogin.Text = Session["loginses"].ToString();
            }
        }

        protected void bJan_Click(object sender, EventArgs e)
        {
            bJan.BackColor = Color.FromArgb(80, 3, 80);
            bJan.ForeColor = Color.FromArgb(243, 228, 166);
            pushedmonths.Add("bJan");
        }

        protected void bFeb_Click(object sender, EventArgs e)
        {
            bFeb.BackColor = Color.FromArgb(80, 3, 80);
            bFeb.ForeColor = Color.FromArgb(243, 228, 166);
            pushedmonths.Add("bFeb");
        }

        protected void bMar_Click(object sender, EventArgs e)
        {
            bMar.BackColor = Color.FromArgb(80, 3, 80);
            bMar.ForeColor = Color.FromArgb(243, 228, 166);
            pushedmonths.Add("bMar");
        }

        protected void bApr_Click(object sender, EventArgs e)
        {
            bApr.BackColor = Color.FromArgb(80, 3, 80);
            bApr.ForeColor = Color.FromArgb(243, 228, 166);
            pushedmonths.Add("bApr");
        }
        protected void bMay_Click(object sender, EventArgs e)
        {
            bMay.BackColor = Color.FromArgb(80, 3, 80);
            bMay.ForeColor = Color.FromArgb(243, 228, 166);
            pushedmonths.Add("bMay");
        }

        protected void bJun_Click(object sender, EventArgs e)
        {
            bJun.BackColor = Color.FromArgb(80, 3, 80);
            bJun.ForeColor = Color.FromArgb(243, 228, 166);
            pushedmonths.Add("bJun");
        }

        protected void bJul_Click(object sender, EventArgs e)
        {
            bJul.BackColor = Color.FromArgb(80, 3, 80);
            bJul.ForeColor = Color.FromArgb(243, 228, 166);
            pushedmonths.Add("bJul");
        }

        protected void bAug_Click(object sender, EventArgs e)
        {
            bAug.BackColor = Color.FromArgb(80, 3, 80);
            bAug.ForeColor = Color.FromArgb(243, 228, 166);
            pushedmonths.Add("bAug");
        }

        protected void bSep_Click(object sender, EventArgs e)
        {
            bSep.BackColor = Color.FromArgb(80, 3, 80);
            bSep.ForeColor = Color.FromArgb(243, 228, 166);
            pushedmonths.Add("bSep");
        }

        protected void bOct_Click(object sender, EventArgs e)
        {
            bOct.BackColor = Color.FromArgb(80, 3, 80);
            bOct.ForeColor = Color.FromArgb(243, 228, 166);
            pushedmonths.Add("bOct");
        }

        protected void bNov_Click(object sender, EventArgs e)
        {
            bNov.BackColor = Color.FromArgb(80, 3, 80);
            bNov.ForeColor = Color.FromArgb(243, 228, 166);
            pushedmonths.Add("bNov");
        }

        protected void bDec_Click(object sender, EventArgs e)
        {
            bDec.BackColor = Color.FromArgb(80, 3, 80);
            bDec.ForeColor = Color.FromArgb(243, 228, 166);
            pushedmonths.Add("bDec");
        }

        protected void ButReset_Click(object sender, EventArgs e)
        {
            string [] months = { "bJan", "bFeb", "bMar","bApr", "bMay", "bJun", "bJul", "bAug", "bSep", "bOct", "bNov", "bDec"};
            for(int i=0;i<12; i++)
            {
                Button bid = FindControl(months[i]) as Button; 
                bid.BackColor = Color.FromArgb(243, 228, 166);
                bid.ForeColor = Color.FromArgb(80, 3, 80);
            }
            //schesuleCaldendar
            pushedmonths.Clear();

        }
        SqlConnection con = new SqlConnection(@"Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=|DataDirectory|\Database1.mdf;Integrated Security=True");
        
        protected void but1_Click(object sender, EventArgs e)
        {
            SqlConnection con = new SqlConnection(@"Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=|DataDirectory|\Database1.mdf;Integrated Security=True");
            string mmm = "";
            HtmlGenericControl newControl = new HtmlGenericControl("div");
            newControl.ID = "divevents";
            newControl.Attributes["class"] = "row";
            foreach (string i in pushedmonths)
            {
                con.Open();
                string selectevent = "Select * From Calendarevents where monthc= '" + i + "' and typec='" + calendCateg.SelectedValue + "'";
                SqlCommand com = new SqlCommand(selectevent,con);
                using (SqlDataReader com_reader = com.ExecuteReader())
                {
                    if(com_reader.Read())
                    {
                        mmm = mmm.Insert(mmm.Length, "<div class='col-lg-4 col-sm-12'><img src='" + com_reader["imagec"].ToString() + "' class='logo' /><h3>"+ com_reader["eventc"].ToString()+"</h3><h4>"+ com_reader["datec"].ToString() + "</h4></div>");
                    }
                    else
                    {

                    }
                }
                con.Close();
                
            }
            newControl.InnerHtml = mmm;
            schesuleCaldendar.Controls.Add(newControl);
        }

        protected void Butsignout_Click(object sender, EventArgs e)
        {
            Session.Clear();
        }
    }
}