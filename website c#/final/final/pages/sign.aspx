<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="sign.aspx.cs" Inherits="final.pages.sign" %>

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
                    <form>
                        <div id="registrationForm">
                            <div class="row">
                                <div class="col-lg-12 col-sm-12">
                                    <h3>Name</h3>
                                    <input  type = "text" id="up-name">
                                    <h3>Last name</h3>
                                    <input  type = "text" id="up-lastname">
                                    <h3>Gender</h3>
                                </div>
                            </div>
                            <div class="row">
                                <div class="col-lg-2 col-sm-2 offset-4">
                                    <p style="margin: 0;">Male</p>
                                </div>
                                <div class="col-lg-2 col-sm-2">
                                    <p style="margin: 0;">Female</p>
                                </div>
                            </div>
                            <div class="row">
                                <div class="col-lg-2 col-sm-2 offset-4">
                                    <input  type = "radio" name = "choice" value =  "choice1">
                                </div>
                                <div class="col-lg-2 col-sm-2">
                                    <input  type = "radio" name = "choice" value =  "choice2">
                                </div>
                            </div>
                            <div class="col-lg-12 col-sm-12">
                                <h3>Date of birth</h3>
                                <input  type="date">
                            </div>
                            <div class="col-lg-12 col-sm-12">
                                <h3>Login</h3>
                                <asp:TextBox ID="loginsign" runat="server"></asp:TextBox>
                            </div>
                            <div class="col-lg-12 col-sm-12">
                                <h3>Password</h3>
                                <asp:TextBox ID="passwordsign" runat="server"></asp:TextBox>
                            </div>
                            <div class="col-lg-12 col-sm-12">
                                <h3>Password confirmation</h3>
                                <input  type="text">
                            </div>
                            <div class="row">
                                <div class="col-lg-4 col-sm-4 offset-2">
                                    <br />
                                    <asp:Button ID="butUp" runat="server" class="enter" Text="Sign up" style="margin-right: 0;" OnClick="butUp_Click" />
                                </div>
                                <div class="col-lg-4 col-sm-4">
                                    <br />
                                    <asp:Button ID="butIn" runat="server" class="enter" Text="Sign in" style="margin-right: 0; color: rgb(80, 3, 80);background-color: rgb(243, 228, 166);" OnClick="butIn_Click"/>
                                </div>
                            </div>
                        </div>
                        <div class="col-lg-12 col-sm-12">
                            <br />
                            <br />
                            <asp:Button ID="butCanc" runat="server" class="cancel" Text="Cancel" OnClick="butCanc_Click" />
                        </div>
                    </form>
                    
                </div>
            </div>
        </div>
    </form>
</body>
</html>
