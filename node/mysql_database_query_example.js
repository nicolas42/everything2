/*
Deploy
rm function.zip; zip -r function.zip index.js node_modules; aws lambda update-function-code --function-name update-database --zip-file fileb://function.zip;

Docs
https://docs.aws.amazon.com/lambda/latest/dg/services-rds-tutorial.html
https://www.npmjs.com/package/mssql




Run this to demo

var update_database = require('./update_database.js');
update_database.handler();


*/

const sql = require('mssql')
var AWS = require('aws-sdk');
const gpmfExtract = require('gpmf-extract');
const goproTelemetry = require(`gopro-telemetry`);
const toGeojson = require('gopro-telemetry/code/toGeojson');

const database = 'mssql://admin:4bMneTY0p6tA@greenview1.coteoxtuwiez.ap-southeast-2.rds.amazonaws.com/greenview-db-1';




exports.handler = function () {


    let filename = 'file' + Date.now().toString();
    let sql1 = `INSERT INTO [dbo].[Media] ([Name],[Ext],[Type],[RelativeTimeUnit],[ObsInstanceId]) VALUES ('${filename}','MP4','VIDEO', 'Milliseconds', (
        SELECT [Id] FROM [ObsInstance] WHERE Code = 'PN' AND ObsDefId = ( SELECT [Id] FROM [ObsDef] WHERE Name = 'Jinglers Creek Org Breakdown Structure' ) ) )`;

    let sql2 = `select * from Media`;

    sql.connect(database, function(err, result){
        sql.query(sql1, function(err, result){
            sql.query(sql2, function(err, result){
                console.dir(result.recordset[result.recordset.length-1]);
                sql.close();
            });
        });
    });


}