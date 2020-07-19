function handleDownload() {
    let csvData = ""
    //defined in ble.js
    driving_log.forEach(function(rowvals) {
    　let row = rowvals.join(",");
    　csvData += row + "\r\n";
    });
    
    var content = csvData;
    var blob = new Blob([ content ], { "type" : "text/csv" });

    if (window.navigator.msSaveBlob) { 
        window.navigator.msSaveBlob(blob, "dlog.csv"); 
        window.navigator.msSaveOrOpenBlob(blob, "dlog.csv"); 
    } else {
        document.getElementById("download").href = window.URL.createObjectURL(blob);
    }
}