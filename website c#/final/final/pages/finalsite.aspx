<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="finalsite.aspx.cs" Inherits="final.pages.finalsite" %>

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
    <style type="text/css">
        .auto-style1 {
            margin-left: 71;
        }
    </style>
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
                    <div>
                        <h1>EVENT DIGEST IN YOUR CITY</h1> 
                    </div>
                       
                </div>
                <div class="news-part" style="margin-top: 30;">
                    <br><h2>NEWS</h2> 
                    <div class="row" style="margin-top: 20;">
                        <div class="col-lg-3 offset-1 col-sm-12">
                            <img src="../images/opern.jpg" class="news animated fadeInLeft">
                        </div>
                        <div class="col-lg-7 offset-1 col-sm-12">
                            <h3>World ballet tour</h3>
                            <p>Ural Opera Ballet Theatre will organize one week of World ballet tour this autumn!</p> 
                        </div>
                    </div>
                    <hr>
                    <div class="row" style="margin-top: 20;">
                        <div class="col-lg-3 offset-1 col-sm-12">
                            <img src="../images/divs.jpg" class="news animated fadeInLeft delay-1s">
                        </div>
                        <div class="col-lg-7 offset-1 col-sm-12">
                            <h3>DIVS is closed for 3 days</h3>
                            <p>The desicion of reconstuction of the entrance was agreed by...</p> 
                        </div>
                    </div>
                    <hr>
                    <div class="row" style="margin-top: 20;">
                        <div class="col-lg-3 offset-1 col-sm-12">
                            <img src="../images/uctus.jpg" class="news animated fadeInLeft delay-2s">
                        </div>
                        <div class="col-lg-7 offset-1 col-sm-12">
                            <h3>Freestyle competition</h3>
                            <p>Uctus has opened a new race for the Freestyle competition.</p> 
                        </div>
                    </div>
                    <hr>
                    <div class="row" style="margin-top: 20;">
                        <div class="col-lg-3 offset-1 col-sm-12">
                            <img src="../images/plot.jpg" class="news animated fadeInLeft delay-3s">
                        </div>
                        <div class="col-lg-7 offset-1 col-sm-12">
                            <h3>New record</h3>
                            <p>The new record of the number of public on the Street concert yesterday.</p> 
                        </div>
                    </div>
                </div>
            </div>
        </div> 
    </form>
</body>
</html>
