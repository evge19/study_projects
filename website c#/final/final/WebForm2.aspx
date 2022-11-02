<%@ Page Theme="Theme1" Title=""  Language="C#" MasterPageFile="~/Site1.Master" AutoEventWireup="true" CodeBehind="WebForm2.aspx.cs" Inherits="final.WebForm2" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">

    <style type="text/css">
        .auto-style1 {
            text-align: center;
        }
        .auto-style2 {
            margin-left: 55px;
        }
        .auto-style3 {
            margin-left: 0px;
        }
    .auto-style4 {
        margin-left: 18px;
    }
        .auto-style5 {
            text-align: left;
        }
    </style>

</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div class="container">
                <div class="main">
                    <div class="part-name">
                        <div class="row">
                            <div class="auto-style5">
                                <asp:Button ID="Butsignout" runat="server" Text="Sign out" OnClick="Butsignout_Click" />
                                <asp:Label ID="Labellogin" runat="server" Text=""></asp:Label>
                            </div>
                            <div class="col-lg-11 col-sm-12">
                                <ul style="font-family:'Archivo Black', sans-serif; font-size: 16;">
                                    
                                    <li><a href="pages/finalsite.aspx" style="color: rgb(80, 3, 80)">Home</a></li>
                                    <li><a href="pages/about.aspx" style="color: rgb(80, 3, 80)">About</a></li>
                                    <li><a href="pages/shop.aspx" style="color: rgb(80, 3, 80)">Shop</a></li>
                                    <li><a href="pages/calendar.aspx" style="color: rgb(80, 3, 80)">Calendar</a></li>
                                    <li><a href="../WebForm2.aspx" style="color: rgb(80, 3, 80)">Q&F</a></li>
                                    <li><a href="pages/sign.aspx" style="color: rgb(80, 3, 80);" class=" sign_anim" >Sign</a></li>
                                </ul>
                            </div>
                        </div>
                    </div>
                    <div class="auto-style1">
                        <br />
                        <h4 style="font-size:20px; font-family: 'Archivo Black', sans-serif; color: rgb(243, 228, 166); background-color: rgb(80, 3, 80); text-align:center" class="auto-style1">Ask question or give feedback!</h4>
                        <asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" ControlToValidate="TextBox1" ErrorMessage="*Enter text" EnableClientScript="False"></asp:RequiredFieldValidator>
                        <br />
                        <asp:TextBox ID="TextBox1" runat="server" Height="113px" Width="382px"></asp:TextBox>
                        <br />
                        <br />
                        <asp:FileUpload ID="FileUpload1" runat="server" CssClass="auto-style3" Width="392px" />
                        <br />
                        <asp:RequiredFieldValidator ID="RequiredFieldValidator3" runat="server" ControlToValidate="TextBox2" ErrorMessage="Enter Email" EnableClientScript="False"></asp:RequiredFieldValidator>
                        <asp:RegularExpressionValidator ID="RegularExpressionValidator1" runat="server" ErrorMessage="Email is not correct" ValidationExpression="\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*" ControlToValidate="TextBox2" EnableClientScript="False"></asp:RegularExpressionValidator>
                        <br />
                        <asp:Label ID="Label1" runat="server" Text="Email"></asp:Label>
                        <asp:TextBox ID="TextBox2" runat="server" Width="273px" CssClass="auto-style4"></asp:TextBox>
                        <asp:Button ID="Button1" class="enter" runat="server" Text="Send" CssClass="auto-style2" Height="35px" Width="58px" OnClick="Button1_Click" />
                        <asp:Label ID="Label2" runat="server" syText="File uploaded"></asp:Label>
                    </div>
                </div>
            </div>
    
</asp:Content>
