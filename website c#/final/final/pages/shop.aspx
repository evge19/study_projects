<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="shop.aspx.cs" Inherits="final.pages.shop" %>

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
                    <h1>EVENT DIGEST IN YOUR CITY</h1>    
                </div>
                <div class="part-content">
                    <div class="news-part" style="margin-top: 30;">
                        <div class="row">
                            <div class="col-lg-4 col-sm-12">
                                <h3>Basket</h3>
                            </div>
                            <div class="col-lg-8 col-sm-12">
                                <h2>Shop</h2>
                            </div>
                        </div>
                        <div class="row" style="margin-top: 20;">
                            <div class="col-lg-4 col-sm-12">
                                <div id="butbas">
                                    <asp:Button ID="butshopshow" runat="server" class="enter butshopanim" Text="Basket" Height="65px" OnClick="butshopshow_Click" />
                                    <br />
                                    <br />
                                    <asp:Button ID="Buttonreturnshop" runat="server" class="cancel" Text="Clear" OnClick="Buttonreturnshop_Click" />
                                </div> 
                            </div>
                            <div runat="server" class="col-lg-8 col-sm-12 row" id="showitems" >
                                
                                
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </form>
</body>
</html>
