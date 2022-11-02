using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace final.pages
{
    public partial class about : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["loginses"] != null)
            {
                Labellogin.Text = Session["loginses"].ToString();
            }
        }

        protected void Butsignout_Click(object sender, EventArgs e)
        {
            Session.Clear();
        }
    }
}