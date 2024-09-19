function doPost(e) {
  // Change the "Timestamp" base on your sheetname
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("Timestamp");

  // Get the data from the request
  var params = e.parameter;

  // Get the current date and time
  var timestamp = new Date();
  
  // Log the button press and time in the sheet
  sheet.appendRow([timestamp, params.buttonState]);

  // Send a response back to the ESP32
  return ContentService.createTextOutput("Button press logged successfully");
}
