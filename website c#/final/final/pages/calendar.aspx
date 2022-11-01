<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="calendar.aspx.cs" Inherits="final.pages.calendar" %>

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
    <script src="../js/script.js"></script>
    <style type="text/css">
        .auto-style1 {
            height: 31px;
        }
        .auto-style2 {
            height: 31px;
            width: 42px;
        }
        .auto-style3 {
            width: 42px;
        }
        .auto-style4 {
            height: 30px;
        }
        .auto-style5 {
            width: 42px;
            height: 30px;
        }
        .auto-style6 {
            width: 315px;
            text-align: left;
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
                    <h1>EVENT DIGEST IN YOUR CITY</h1>    
                </div>
                <div class="part-content">
                    <div class="news-part" style="margin-top: 30;">
                        <div class="row">
                            <div class="col-lg-4 col-sm-12">
                                <h3>Filters</h3>
                            </div>
                            <div class="col-lg-8 col-sm-12">
                                <h2 class="logo_anim">Soon</h2>
                            </div>
                        </div>
                        <div class="row" style="margin-top: 20;">
                            <div class="col-lg-4 col-sm-12">
                                <h4>Choose category</h4>
                                <asp:DropDownList ID="calendCateg" runat="server">
                                    <asp:ListItem></asp:ListItem>
                                    <asp:ListItem>Sport</asp:ListItem>
                                    <asp:ListItem>Music</asp:ListItem>
                                    <asp:ListItem>Art</asp:ListItem>
                                </asp:DropDownList>
                                &nbsp;<h4>Choose month</h4>
                                <asp:ScriptManager ID="ScriptManager1" runat="server"></asp:ScriptManager>
                                
                                <asp:UpdatePanel ID="UpdatePanel1" runat="server">
                                    <ContentTemplate>
                                        <div style="margin-left: 205; margin-top: 20; " class="auto-style6">
                                            &nbsp;<table border="1" style="text-align: center; " class="offset-4-lg" align="center">
                                                <tr><th class="auto-style1">
                                                    <asp:Button ID="bJan" runat="server" Text="Jan" class="tablebut" OnClick="bJan_Click" Height="31px" Width="42px" />
                                                    </th><th class="auto-style1">
                                                        <asp:Button ID="bFeb" runat="server" Text="Feb" class="tablebut" OnClick="bFeb_Click" Height="31px" Width="42px" />
                                                    </th><th class="auto-style2">
                                                        <asp:Button ID="bMar" runat="server" Text="Mar" class="tablebut" OnClick="bMar_Click" Height="31px" Width="42px"/>
                                                    </th></tr>
                                                <tr><th>
                                                    <asp:Button ID="bApr" runat="server" Text="Apr" class="tablebut" OnClick="bApr_Click" Height="31px" Width="42px" />
                                                    </th><th>
                                                        <asp:Button ID="bMay" runat="server" Text="May" class="tablebut" Height="31px" OnClick="bMay_Click" Width="42px" />
                                                    </th><th class="auto-style3">
                                                        <asp:Button ID="bJun" runat="server" Text="Jun" class="tablebut" Height="31px" OnClick="bJun_Click" Width="42px" />
                                                    </th></tr>
                                                <tr><th>
                                                    <asp:Button ID="bJul" runat="server" Text="Jul" class="tablebut" Height="31px" OnClick="bJul_Click" Width="42px" />
                                                    </th><th>
                                                        <asp:Button ID="bAug" runat="server" Text="Aug" class="tablebut" OnClick="bAug_Click" Height="31px" Width="42px" />
                                                    </th><th class="auto-style3">
                                                        <asp:Button ID="bSep" runat="server" Text="Sep" class="tablebut" OnClick="bSep_Click" Height="31px" Width="42px" />
                                                    </th></tr>
                                                <tr><th class="auto-style4">
                                                    <asp:Button ID="bOct" runat="server" Text="Oct" class="tablebut" OnClick="bOct_Click" Height="31px" Width="42px" />
                                                    </th><th class="auto-style4">
                                                        <asp:Button ID="bNov" runat="server" Text="Nov" class="tablebut" OnClick="bNov_Click" Height="31px" Width="42px" />
                                                    </th><th class="auto-style5">
                                                        <asp:Button ID="bDec" runat="server" Text="Dec" class="tablebut" OnClick="bDec_Click" Height="31px" Width="42px"/>
                                                    </th>
                                                </tr>
                                            </table>
                                        </div>
                                    </ContentTemplate>
                                </asp:UpdatePanel>
                                
                                <br />
                                
                                <asp:Button ID="but1" runat="server" class="enter" Text="Show" OnClick="but1_Click" />
                                <asp:Button ID="ButReset" runat="server"  class="cancel" Text="Reset" OnClick="ButReset_Click" />
                                
                                
                                
                            </div>
                            <div class="text-center col-lg-8 col-sm-12">
                                <div runat="server" class="row" id="schesuleCaldendar">

                                </div>
                                
                            </div>
                            
                        </div>
                </div>
            </div>
        </div>
    </form>
</body>
</html>
