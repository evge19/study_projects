using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;
using System.Web.UI.HtmlControls;

namespace final.pages
{
    public partial class shop : System.Web.UI.Page
    {
        public static List<string> chosenitems = new List<string>();
        //public static string chosenitems = "";
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["loginses"] != null)
            {
                Labellogin.Text = Session["loginses"].ToString();
            }
            SqlConnection con = new SqlConnection(@"Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=|DataDirectory|\Database1.mdf;Integrated Security=True");
            
            DataSet4 data = new DataSet4();
            
            string selectrows = "Select * From Shopitems";
            SqlCommand comrow = new SqlCommand(selectrows, con);
            SqlDataAdapter adp = new SqlDataAdapter(comrow.CommandText, con);
            adp.Fill(data, "Shopitems");
            int rowCount = data.Tables["Shopitems"].Rows.Count;
            
            
            //check.Text = rowCount.ToString();


            for (int i=1;i<=rowCount;i++)
            {
                con.Open();
                
                string selectevent = "Select * From Shopitems where Id='"+i+ "'";
                SqlCommand com = new SqlCommand(selectevent, con);
                using (SqlDataReader com_reader = com.ExecuteReader())
                {
                    if (com_reader.Read())
                    {
                        HtmlGenericControl shopdiv = new HtmlGenericControl("div");
                        shopdiv.ID = "divshop"+i.ToString();
                        shopdiv.Attributes["class"] = "col-lg-4 col-sm-12";
                        Image imgshop = new Image();
                        imgshop.ImageUrl = com_reader["imagesh"].ToString().Replace(" ","");
                        imgshop.Attributes.Add("width", "100");
                        imgshop.Attributes.Add("height", "auto");
                        Label labelname = new Label()
                        {
                            Text = "<br>" + com_reader["namesh"].ToString()+"<br>"+ com_reader["pricesh"].ToString()+"<br>"

                        };
                        CheckBox itemcheck = new CheckBox();
                        itemcheck.ID = "useritem" + i.ToString();
                        itemcheck.Attributes.Add("AutoPostBack", "true");
                        itemcheck.Attributes.Add("Checked", "false");
                        itemcheck.CheckedChanged += Itemcheck_CheckedChanged;
                        /*Label labelprice = new Label()
                        {
                            Text = com_reader["pricesh"].ToString()
                        };*/
                        //nnn = "<div class='col-lg-4 col-sm-12'><img src='" + com_reader["imagesh"].ToString() + "' class='logo' /><h3>" + com_reader["namesh"].ToString() + "</h3><h4>" + com_reader["pricesh"].ToString() + "</h4></div>";
                        shopdiv.Controls.Add(imgshop);
                        shopdiv.Controls.Add(labelname);
                        shopdiv.Controls.Add(itemcheck);

                        //shopdiv.Controls.Add(labelprice);
                        //shopdiv.InnerHtml = "<br />";
                        showitems.Controls.Add(shopdiv);

                    }
                    else
                    {

                    }
                }
                con.Close();

            }
            
            
        }

        private void Itemcheck_CheckedChanged(object sender, EventArgs e)
        {
            chosenitems.Add(((CheckBox)sender).ClientID);
            //chosenitems.Add("УРАА");
            //throw new NotImplementedException();
            


        }

        protected void butshopshow_Click(object sender, EventArgs e)
        {
            showitems.Controls.Clear();
            string mmm = "";
            SqlConnection con = new SqlConnection(@"Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=|DataDirectory|\Database1.mdf;Integrated Security=True");

                        
            foreach (string i in chosenitems)
            {

                con.Open();

                string selectevent = "Select * From Shopitems where Id='" + i.Replace("useritem", "") + "'";
                SqlCommand com = new SqlCommand(selectevent, con);
                using (SqlDataReader com_reader = com.ExecuteReader())
                {
                    if (com_reader.Read())
                    {
                        HtmlGenericControl shopdivbasket = new HtmlGenericControl("div");
                        shopdivbasket.ID = "divshopbasket" + i.Replace("useritem", "");
                        shopdivbasket.Attributes["class"] = "col-lg-4 col-sm-12";
                        Image imgshop = new Image();
                        imgshop.ImageUrl = com_reader["imagesh"].ToString().Replace(" ", "");
                        imgshop.Attributes.Add("width", "100");
                        imgshop.Attributes.Add("height", "auto");
                        Label labelname = new Label()
                        {
                            Text = "<br>" + com_reader["namesh"].ToString() + "<br>" + com_reader["pricesh"].ToString()

                        };

                        /*Label labelprice = new Label()
                        {
                            Text = com_reader["pricesh"].ToString()
                        };*/
                        //nnn = "<div class='col-lg-4 col-sm-12'><img src='" + com_reader["imagesh"].ToString() + "' class='logo' /><h3>" + com_reader["namesh"].ToString() + "</h3><h4>" + com_reader["pricesh"].ToString() + "</h4></div>";
                        shopdivbasket.Controls.Add(imgshop);
                        shopdivbasket.Controls.Add(labelname);

                        //shopdiv.Controls.Add(labelprice);
                        //shopdiv.InnerHtml = "<br />";
                        showitems.Controls.Add(shopdivbasket);

                    }
                    else
                    {

                    }
                }
                con.Close();
                mmm =mmm.Insert(mmm.Length, i.Replace("useritem", ""));
            }

        }

        protected void Butsignout_Click(object sender, EventArgs e)
        {
            Session.Clear();
        }

        protected void Buttonreturnshop_Click(object sender, EventArgs e)
        {
            Response.Redirect("shop.aspx");
        }
    }
}