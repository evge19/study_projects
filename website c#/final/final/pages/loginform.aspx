<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="loginform.aspx.cs" Inherits="final.pages.loginform" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title>Event Digest</title>
    <link rel="icon" href="city.png" sizes="16x16 32х32" />
    <link rel="preconnect" href="https://fonts.gstatic.com" />
    <link href="https://fonts.googleapis.com/css2?family=Archivo+Black&display=swap" rel="stylesheet" />
    <link href="../css/styles.css" rel="stylesheet" />
    <link rel="stylesheet" href="bootstrap-4.5.3-dist/css/bootstrap.min.css" />
    <link rel="stylesheet" href="animate.min.css" />
</head>
<body>
    <form id="form1" runat="server">
        <div class="container">
            <div class="main"  style="margin-right: 30%; margin-left: 30%;">
                <div class="part-name-sign">
                    <h1>Sign</h1>    
                </div>
                <div class="part-content">
                    <div class="col-lg-12 col-sm-12">
                        <h3>Login</h3>
                        <asp:TextBox ID="loginlogin" runat="server"></asp:TextBox>
                    </div>
                    <div class="col-lg-12 col-sm-12">
                        <h3>Password</h3>
                        <asp:TextBox ID="password" runat="server"></asp:TextBox>
                        <br />
                        <br />
                        <asp:Label ID="Label1" runat="server" Text=""></asp:Label>
                        <br />
                    </div>
                    
                    <div class="col-lg-12 col-sm-12">
                        <asp:Button ID="butOk" runat="server" class="enter" Text="Ok" style="margin-right:0;" OnClick="butOk_Click"/>
                        <br />
                        <br />
                        <asp:Button ID="butCanc" runat="server" class="cancel" Text="Home" OnClick="butCanc_Click" />
                    </div>
                </div>
            </div>
        </div>
        
    </form>
</body>
</html>
