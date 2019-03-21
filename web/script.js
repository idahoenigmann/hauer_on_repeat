fetch('cnt.txt')
    .then(response => response.text())
    .then(text => {
        if (text === "") {
            document.getElementById("cntButtons").innerHTML = "Es müssen noch 12 von 12 Tastern gedrückt werden. <br> " + text + " out of 12 buttons still to be pressed.";
        } else if (text === "1") {
            document.getElementById("cntButtons").innerHTML = "Es muss noch " + text + " von 12 Tastern gedrückt werden. <br>" + text + " out of 12 button still to be pressed.";
        } else if (text === "0") {
            document.getElementById("cntButtons").innerHTML = "Bitte warten - Ihr Zwölftonspiel wird erstellt ... <br> Please wait - your twelve-tone piece is being generated ...";
        } else {
            document.getElementById("cntButtons").innerHTML = "Es müssen noch " + text + " von 12 Tastern gedrückt werden. <br> " + text + " out of 12 buttons still to be pressed.";
        }});

function fadew() {
    $("body").fadeOut();
}

function setupLines() {
    var c = document.getElementById("notenschrift");
    var ctx = c.getContext("2d");

    //#0
    ctx.moveTo(0,0);
    ctx.lineTo(c.width, 0);

    //#1
    ctx.moveTo(0,20);
    ctx.lineTo(c.width, 20);

    //#2
    ctx.moveTo(0,40);
    ctx.lineTo(c.width, 40);

    //#3
    ctx.moveTo(0,70);
    ctx.lineTo(c.width, 70);

    //#4
    ctx.moveTo(0,90);
    ctx.lineTo(c.width, 90);

    //#5
    ctx.moveTo(0,120);
    ctx.lineTo(c.width, 120);

    //#6
    ctx.moveTo(0,140);
    ctx.lineTo(c.width, 140);

    //#7
    ctx.moveTo(0,160);
    ctx.lineTo(c.width, 160);

    //#8
    ctx.moveTo(0,190);
    ctx.lineTo(c.width, 190);

    //#9
    ctx.moveTo(0,210);
    ctx.lineTo(c.width, 210);

    ctx.stroke();
}

function parseAndDraw(XMLContent) {

    var c = document.getElementById("notenschrift");
    var ctx = c.getContext("2d");

    parser = new DOMParser();
    xmlDoc = parser.parseFromString(XMLContent,"text/xml");

    var erg = xmlDoc.getElementsByTagName("bar");

    //console.log(erg);
    for (var i=0; i<erg.length; i++) {
        var childs = erg[i].childNodes;

        console.log("Bar #" + i);
        //console.log(childs)

        var pre_number = 11;
        var color = "black";
        var moveBeside = 0;

        for (var e=0; e<childs.length; e++) {
            if (childs[e].nodeName === "note") {
                var note = childs[e].attributes["filled"];
                var number = parseInt(childs[e].innerHTML);

                if (e+2 < childs.length) {
                    var next_number = parseInt(childs[e+2].innerHTML);
                    //console.log(next_number - number);
                }
                //console.log(childs);
                if ((number - pre_number) == 1 || (next_number - number) == 1) {
                    //color = "red";
                    moveBeside += 1;
                } else {
                    //color = "black"
                    moveBeside = 0;
                }
                pre_number = number;
                if (note !== undefined) {
                    console.log(moveBeside);
                    if (moveBeside == 1) {
                        var x = ((125 * i)+9) + 3;
                        moveBeside += 1;
                    } else if (moveBeside == 2){
                        var x = ((125 * i)+9) + 37;
                    }
                    else {
                        var x = ((125 * i)+9) + 20;
                    }


                    var y = 180 - (number * 10) + 40;
                    var scale = 5.2;

                    ctx.beginPath();
                    ctx.fillStyle = color;
                    ctx.ellipse(x, y, 50 / scale, 75 / scale, Math.PI / 2, 0, 2 * Math.PI);
                    ctx.fill();
                    ctx.beginPath();
                    ctx.ellipse(x, y, 33 / scale, 47 / scale, Math.PI * -1.15, 0, 2 * Math.PI);
                    ctx.fillStyle = "white";
                    ctx.fill();



                } else {


                    console.log(moveBeside);
                    if (moveBeside == 1) {
                        var x = ((125 * i)+9) + 3;
                        moveBeside += 1;
                    } else if (moveBeside == 2){
                        var x = ((125 * i)+9) + 37;
                    }
                    else {
                        var x = ((125 * i)+9) + 20;
                    }

                    var y = 180 - (number * 10) + 40;
                    var scale = 5.2;

                    ctx.beginPath();
                    ctx.fillStyle = color;
                    ctx.arc(x,y,7,0,2*Math.PI);
                    ctx.fill();

                }

            }
        }

    }
}

function cl() {
    window.open('','_self').focus();
    window.close();
}