//calendar
var month=[0,0,0,0,0,0,0,0,0,0,0,0];

function changecolor(x,m) {
    document.getElementById(x).style.backgroundColor = "#3a0e5a";
    document.getElementById(x).style.color = "#ffffff"; 
    month[m]=1;
}
var jan=['<div class="col-lg-4 col-sm-12" class="calen"><img src="images/snowboard.png" class="logo"><h3>Snowboard competition</h3><h4>9 January</h4></div>','<div class="col-lg-4 col-sm-12" class="calen"><img src="images/ski.png" class="logo"><h3>Ski competition</h3><h4>17 January</h4></div>','<div class="col-lg-4 col-sm-12" class="calen"><img src="images/museum1.png" class="logo"><h3>Museum Exhibition</h3><h4>29 January</h4></div>'];
var feb=['<div class="col-lg-4 col-sm-12" class="calen"><img src="images/runskate.png" class="logo"><h3>Skating sport</h3><h4>15 February</h4></div>','<div class="col-lg-4 col-sm-12" class="calen"><img src="images/concert2.png" class="logo"><h3>Music concert</h3><h4>22 February</h4></div>'];
var mar=['<div class="col-lg-4 col-sm-12" class="calen"><img src="images/art.png" class="logo"><h3>Art Galery opening</h3><h4>10 March</h4></div>','<div class="col-lg-4 col-sm-12" class="calen"><img src="images/theatre.png" class="logo"><h3>Opera</h3><h4>18 March</h4></div>'];
var apr=['<div class="col-lg-4 col-sm-12" class="calen"><img src="images/football.png" class="logo"><h3>Football game</h3><h4>6 April</h4></div>','<div class="col-lg-4 col-sm-12" class="calen"><img src="images/concert1.png" class="logo"><h3>Piano concert</h3><h4>10 April</h4></div>','<div class="col-lg-4 col-sm-12" class="calen"><img src="images/basketball.png" class="logo"><h3>Basketball game</h3><h4>14 April</h4></div>'];
var may=[];
var jun=[];
var jul=[];
var sep=[];
var oct=[];
var nov=[];
var dec=[];
var eventmonth=[jan,feb,mar,apr,may,jun,jul,sep,oct,nov,dec];
var sport=['<div class="col-lg-4 col-sm-12" class="calen"><img src="images/snowboard.png" class="logo"><h3>Snowboard competition</h3><h4>9 January</h4></div>','<div class="col-lg-4 col-sm-12" class="calen"><img src="images/ski.png" class="logo"><h3>Ski competition</h3><h4>17 January</h4></div>','<div class="col-lg-4 col-sm-12" class="calen"><img src="images/runskate.png" class="logo"><h3>Skating sport</h3><h4>15 February</h4></div>','<div class="col-lg-4 col-sm-12" class="calen"><img src="images/football.png" class="logo"><h3>Football game</h3><h4>6 April</h4></div>','<div class="col-lg-4" class="calen"><img src="images/basketball.png" class="logo"><h3>Basketball game</h3><h4>14 April</h4></div>']
var music=['<div class="col-lg-4 col-sm-12" class="calen"><img src="images/concert2.png" class="logo"><h3>Music concert</h3><h4>22 February</h4></div>','<div class="col-lg-4 col-sm-12" class="calen"><img src="images/concert1.png" class="logo"><h3>Piano concert</h3><h4>10 April</h4></div>'];
var art=['<div class="col-lg-4 col-sm-12" class="calen"><img src="images/museum1.png" class="logo"><h3>Museum Exhibition</h3><h4>29 January</h4></div>','<div class="col-lg-4 col-sm-12" class="calen"><img src="images/art.png" class="logo"><h3>Art Galery opening</h3><h4>10 March</h4></div>','<div class="col-lg-4 col-sm-12" class="calen"><img src="images/theatre.png" class="logo"><h3>Opera</h3><h4>18 March</h4></div>'];

function showCalendar(){
    if(document.getElementById("calend-categ").value=="All"){
        $("#schesuleCaldendar").empty();
        for(var i=0;i<12;i++)
        {
            if(month[i]==1)
            {
                $('#schesuleCaldendar').append(eventmonth[i]);
            }
            
        } 
    }
    else if(document.getElementById("calend-categ").value=="Sport"){
        $("#schesuleCaldendar").empty();
        for(var i=0;i<12;i++)
        {
            if(month[i]==1)
            {
                for(var j=0;j<eventmonth[i].length;j++)
                {
                    for(var k=0;k<sport.length;k++)
                    {
                        if(eventmonth[i][j]==sport[k])
                        {
                            $('#schesuleCaldendar').append(sport[k]);
                        }
                    }
                    
                }
                    
            }
        }
          
    }
    else if(document.getElementById("calend-categ").value=="Music"){
        $("#schesuleCaldendar").empty();
        for(var i=0;i<12;i++)
        {
            if(month[i]==1)
            {
                for(var j=0;j<eventmonth[i].length;j++)
                {
                    for(var k=0;k<music.length;k++)
                    {
                        if(eventmonth[i][j]==music[k])
                        {
                            $('#schesuleCaldendar').append(music[k]);
                        }
                    }
                    
                }
                    
            }
        } 
    }
    else if(document.getElementById("calend-categ").value=="Art"){
        $("#schesuleCaldendar").empty();
        for(var i=0;i<12;i++)
        {
            if(month[i]==1)
            {
                for(var j=0;j<eventmonth[i].length;j++)
                {
                    for(var k=0;k<art.length;k++)
                    {
                        if(eventmonth[i][j]==art[k])
                        {
                            $('#schesuleCaldendar').append(art[k]);
                        }
                    }
                    
                }
                    
            }
        }
    }
    
}
//sign

function signUp(){
    alert(document.getElementById("up-name").value+" "+document.getElementById("up-lastname").value+", You are with us!");
    document.location.href = "finalsite.html";
}
function signIn(){
    document.getElementById("registrationForm").innerHTML = '<div class="col-lg-12 col-sm-12"><h3>Login</h3><input  type="text" id="loginlogin"></div><div class="col-lg-12 col-sm-12"><h3>Password</h3><input  type="text"></div><button type="button" name="but-ok" class="enter" style="margin-right:0;" onclick="signInAlert()">OK</button>';
}

function signInAlert(){
    alert("Welcome!");
    // loginlog= document.getElementById("loginlogin").value;
    $(document).ready(function(){
        document.location.href = "finalsite.html";
    });
    
    // $("#loginname").append("<p>"+document.getElementById("loginlogin").value+"</p>");

}
// var loginlog;
// function loginpage(){
//     loginlog=document.getElementById("loginlogin").value;
//     $("#ddd").empty();
//     $('#ddd').append("<h1>"+loginlog+"</h1>");
//     alert(loginlog);
// }
var shopitem=["1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18"];
var itemname=["T-shirt","T-shirt","T-shirt","T-shirt","T-shirt","Hoody","Hoody","Hoody","Mug","Mug","Mug","Mug","Bottle","Bottle x2","Plate","Notebook","Notebook","Pen"]
var price=["7$/100 points","7$/100 points","7$/100 points","7$/100 points","9$/130 points","15$/200 points","16$/210 points","16$/210 points","10$/140 points","8$/120 points","7$/100 points","8$/120 points","3$/60 points","3$/60 points","2$/40 points","1$/20 points","1$/20 points","0.1$/5 points"];
function loginpageshop(){   //all
    for( var i=0;i<shopitem.length;i++)
    {
        $('#shoprow').append(`<div class="col-lg-4 col-sm-12 shop">
        <img src="images/shop/`+shopitem[i]+`.jpg" class="logo">
        <h3>`+itemname[i]+`</h3>
        <h4>`+price[i]+`</h4></div>`);
    }
    
}
function getclothes(x){
    x = document.getElementById(x);
    if (x.checked==true){
        for( var i=0;i<8;i++)
        {
            $('#shoprowclothes').append(`<div class="col-lg-4 col-sm-12 shop">
            <img src="images/shop/`+shopitem[i]+`.jpg" class="logo">
            <h3>`+itemname[i]+`</h3>
            <h4>`+price[i]+`</h4><input  type = "checkbox" id="idoffice"  onchange = "choicebasket(`+i+`)"></div>`);
        }
    }
    else if (x.checked==false){
        $('#shoprowclothes').empty();
    }
}
function gethause(y){
    y = document.getElementById(y);
    if (y.checked==true){
        for( var i=8;i<15;i++)
        {
            $('#shoprowhause').append(`<div class="col-lg-4 col-sm-12 shop">
            <img src="images/shop/`+shopitem[i]+`.jpg" class="logo">
            <h3>`+itemname[i]+`</h3>
            <h4>`+price[i]+`</h4><input  type = "checkbox" id="idoffice"  onchange = "choicebasket(`+i+`)"></div>`);
        }
    }
    else if (y.checked==false){
        $('#shoprowhause').empty();
    }
}
function getoffice(z){
    z = document.getElementById(z);
    if (z.checked==true){
        for( var i=15;i<18;i++)
        {
            $('#shoprowoffice').append(`<div class="col-lg-4 col-sm-12 shop">
            <img src="images/shop/`+shopitem[i]+`.jpg" class="logo">
            <h3>`+itemname[i]+`</h3>
            <h4>`+price[i]+`</h4><input  type = "checkbox" id="idoffice"  onchange = "choicebasket(`+i+`)"></div>`);
        }
    }
    else if (z.checked==false){
        $('#shoprowoffice').empty();
    }
}
function loginpageshop(){   //all
    getclothes("idclothes");
    gethause("idhause");
    getoffice("idoffice");
    
    // for( var i=0;i<shopitem.length;i++)
    // {
    //     $('#shoprow').append(`<div class="col-lg-4" class="calen">
    //     <img src="images/shop/`+shopitem[i]+`.jpg" class="logo">
    //     <h3>`+itemname[i]+`</h3>
    //     <h4>`+price[i]+`</h4></div>`);
    // }
    
}
var chosenitems=[];
function choicebasket(q){
    chosenitems.push(q);
}
function choicepageshop(){
    $('#showbasket').empty();
    for( var i=0;i<chosenitems.length;i++)
        {
            $('#showbasket').append(`<div class="col-lg-4 col-sm-12 shop">
            <img src="images/shop/`+shopitem[chosenitems[i]]+`.jpg" class="logo">
            <h3>`+itemname[chosenitems[i]]+`</h3>
            <h4>`+price[chosenitems[i]]+`</h4></div>`);
        }
    $('#butbas').empty();
    $('#butbas').append(`<button type="button" name="but-canc" class="cancel" onclick="location.href='shop.html'">Return</button>`);
}

