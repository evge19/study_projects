<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="about.aspx.cs" Inherits="final.pages.about" %>

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
            <div class="main">
                <div class="part-name">
                    <div class="row">
                        <div class="col-lg-1">
                            <asp:Button ID="Butsignout" runat="server" class="cancel" Text="Sign out" OnClick="Butsignout_Click" />
                            <asp:Label ID="Labellogin" runat="server" Text=""></asp:Label>
                        </div>
                        <div class="col-lg-11 col-sm-12">
                            <ul style="font-family:'Archivo Black', sans-serif; font-size: 16;">
                                <li><a href="finalsite.aspx" style="color: rgb(80, 3, 80)">Home</a></li>
                                <li><a href="about.aspx" style="color: rgb(80, 3, 80)">About</a></li>
                                <li><a href="shop.aspx" style="color: rgb(80, 3, 80)">Shop</a></li>
                                <li><a href="calendar.aspx" style="color: rgb(80, 3, 80)">Calendar</a></li>
                                <li><a href="../WebForm2.aspx" style="color: rgb(80, 3, 80)">Q&F</a></li>
                                <li><a href="sign.aspx" style="color: rgb(80, 3, 80);" class=" sign_anim" >Sign</a></li>
                                
                            </ul>
                        </div>
                    </div>
                    <h1>ABOUT</h1>    
                </div>
                <div class="part-content">
                    <h2>What</h2>
                    <p  class="pAbout">This is a program where you can join events and get points.</p>
                    <h2>How</h2>
                    <p  class="pAbout">Just sign up and get the fan-passport where you can mark your particioations</p>
                    <h2>Points</h2>
                    <p  class="pAbout">Earn points and buy our staff at Shop.</p>
                    <h2>Contact us:</h2>
                    <p  class="pAbout">Email:event@digest.com <br> Telephone:+123456789</p>
                </div>
            </div>
        </div>
    </form>
</body>
</html>
