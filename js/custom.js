$(document).ready(function() {

    var url = 'http://one.api.botbook.com/add/4kzxV3BUgl7/?x=';

    // Network functions

    function sendGuardModeOn() {
        send(66);
    }

    function sendGuardModeOff() {
        send(55);
    }

    function sendAlarmOff() {
        send(44);
    }

    function sendDoorStatus() {
        send(33);
    }

    function sendDone(res) {
        $("#status").text(res);
        $("#status").show();
        $("#status").delay(1500).fadeOut("slow");
    }

    function send(x) {
        var corsOptions = {
            url: url + x,
            type: "GET",
            success: sendDone,
            error: sendDone,
        };
        jQuery.ajax(corsOptions);
    }

    // Event functions

    function onReady() {
        $("#nojs").hide();

        $("#apiURL").text(url);
        $("#apiURL").attr("href", url);

        $("#guardModeOn").click(sendGuardModeOn);
        $("#guardModeOff").click(sendGuardModeOff);
        $("#sendAlarmOff").click(sendAlarmOff);
        $("#sendDoorStatus").click(sendDoorStatus);


        $("#status").text("");
        $("#status").delay(1500).fadeOut("slow");
    }
    jQuery(document).ready(onReady);
});

$(document).ready(function() {
    $("#alarmStatus").click(function() {
        $.get("http://one.api.botbook.com/last/wx8ETBcLFey", function(data, status) {
            if (data == 66.0) {
                status = "Guardmode On";
                alert("Code: " + data + "\nStatus: " + status);
            } else if (data == 55.0) {
                status = "Guardmode Off"
                alert("Code: " + data + "\nStatus: " + status);
            } else if (data == 44.0) {
                status = "Alarm Off"
                alert("Code: " + data + "\nStatus: " + status);
            } else if (data == 100.0) {
                status = "Alarm is on!"
                alert("Code: " + data + "\nStatus: " + status);
            }
        });
    });
});
