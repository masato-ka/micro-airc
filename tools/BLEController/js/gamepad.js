let connectedGamepadIndex;
let loopID
const AXIS_L_HORIZONTAL_INDEX = 0;
const AXIS_L_VERTICAL_INDEX   = 1;
const AXIS_R_HORIZONTAL_INDEX = 2;
const AXIS_R_VERTICAL_INDEX   = 5;


addEventListener("gamepadconnected", (e) => {
    let gamepad = e.gamepad;
    console.log("Connected Controller");
    console.log("Index: %d, ID: %s, Type: %s",
                gamepad.index, gamepad.id, gamepad.mapping);
    connectedGamepadIndex = gamepad.index
    loopID = requestAnimationFrame(loop);
});

addEventListener("gamepaddisconnected", (e) => {
    let gamepad = e.gamepad;
    console.log("Disconnected controller");
    console.log("Index: %d, ID: %s, Type: %s",
                gamepad.index, gamepad.id, gamepad.mapping);
    connectedGamepadIndex =null;
    cancelAnimationFrame(loopID);
});


function loop(timestamp) {
    var gamepads = navigator.getGamepads();
    var gp = gamepads[connectedGamepadIndex];

    var leftAxisHorizontal = gp.axes[AXIS_L_HORIZONTAL_INDEX];
    var leftAxisVertical = gp.axes[AXIS_L_VERTICAL_INDEX];
    var rightAxisHorizontal = gp.axes[AXIS_R_HORIZONTAL_INDEX];
    var rightAxisVertical = gp.axes[AXIS_R_VERTICAL_INDEX];

    throttle = leftAxisVertical*-1.0;
    steering = rightAxisHorizontal*-1.0;
    var send_dataview = new DataView(arrayBuffer);
    send_dataview.setFloat32(0,throttle,true);
    send_dataview.setFloat32(4,steering,true);
    txCharacteristic.writeValue(send_dataview.buffer);  //Defined in ble.js
    requestAnimationFrame(loop);
}