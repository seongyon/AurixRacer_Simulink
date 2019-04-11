function CodeDefine() { 
this.def = new Array();
this.def["IR_Controller_DWork"] = {file: "IR_Controller_c.html",line:22,type:"var"};
this.def["IR_Controller_step"] = {file: "IR_Controller_c.html",line:25,type:"fcn"};
this.def["IR_Controller_initialize"] = {file: "IR_Controller_c.html",line:134,type:"fcn"};
this.def["D_Work_IR_Controller"] = {file: "IR_Controller_h.html",line:37,type:"type"};
this.def["pid_param"] = {file: "IR_Controller_types_h.html",line:29,type:"type"};
this.def["Parameters_IR_Controller"] = {file: "IR_Controller_types_h.html",line:34,type:"type"};
this.def["IR_Controller_P"] = {file: "IR_Controller_data_c.html",line:20,type:"var"};
this.def["int8_T"] = {file: "rtwtypes_h.html",line:47,type:"type"};
this.def["uint8_T"] = {file: "rtwtypes_h.html",line:48,type:"type"};
this.def["int16_T"] = {file: "rtwtypes_h.html",line:49,type:"type"};
this.def["uint16_T"] = {file: "rtwtypes_h.html",line:50,type:"type"};
this.def["int32_T"] = {file: "rtwtypes_h.html",line:51,type:"type"};
this.def["uint32_T"] = {file: "rtwtypes_h.html",line:52,type:"type"};
this.def["real32_T"] = {file: "rtwtypes_h.html",line:53,type:"type"};
this.def["real64_T"] = {file: "rtwtypes_h.html",line:54,type:"type"};
this.def["real_T"] = {file: "rtwtypes_h.html",line:60,type:"type"};
this.def["time_T"] = {file: "rtwtypes_h.html",line:61,type:"type"};
this.def["boolean_T"] = {file: "rtwtypes_h.html",line:62,type:"type"};
this.def["int_T"] = {file: "rtwtypes_h.html",line:63,type:"type"};
this.def["uint_T"] = {file: "rtwtypes_h.html",line:64,type:"type"};
this.def["ulong_T"] = {file: "rtwtypes_h.html",line:65,type:"type"};
this.def["char_T"] = {file: "rtwtypes_h.html",line:66,type:"type"};
this.def["uchar_T"] = {file: "rtwtypes_h.html",line:67,type:"type"};
this.def["byte_T"] = {file: "rtwtypes_h.html",line:68,type:"type"};
this.def["creal32_T"] = {file: "rtwtypes_h.html",line:81,type:"type"};
this.def["creal64_T"] = {file: "rtwtypes_h.html",line:89,type:"type"};
this.def["creal_T"] = {file: "rtwtypes_h.html",line:97,type:"type"};
this.def["cint8_T"] = {file: "rtwtypes_h.html",line:107,type:"type"};
this.def["cuint8_T"] = {file: "rtwtypes_h.html",line:117,type:"type"};
this.def["cint16_T"] = {file: "rtwtypes_h.html",line:127,type:"type"};
this.def["cuint16_T"] = {file: "rtwtypes_h.html",line:137,type:"type"};
this.def["cint32_T"] = {file: "rtwtypes_h.html",line:147,type:"type"};
this.def["cuint32_T"] = {file: "rtwtypes_h.html",line:157,type:"type"};
this.def["pointer_T"] = {file: "rtwtypes_h.html",line:175,type:"type"};
}
CodeDefine.instance = new CodeDefine();
var testHarnessInfo = {OwnerFileName: "", HarnessOwner: "", HarnessName: "", IsTestHarness: "0"};
var relPathToBuildDir = "../ert_main.c";
var fileSep = "\\";
var isPC = true;
function Html2SrcLink() {
	this.html2SrcPath = new Array;
	this.html2Root = new Array;
	this.html2SrcPath["IR_Controller_c.html"] = "../IR_Controller.c";
	this.html2Root["IR_Controller_c.html"] = "IR_Controller_c.html";
	this.html2SrcPath["IR_Controller_h.html"] = "../IR_Controller.h";
	this.html2Root["IR_Controller_h.html"] = "IR_Controller_h.html";
	this.html2SrcPath["IR_Controller_private_h.html"] = "../IR_Controller_private.h";
	this.html2Root["IR_Controller_private_h.html"] = "IR_Controller_private_h.html";
	this.html2SrcPath["IR_Controller_types_h.html"] = "../IR_Controller_types.h";
	this.html2Root["IR_Controller_types_h.html"] = "IR_Controller_types_h.html";
	this.html2SrcPath["IR_Controller_data_c.html"] = "../IR_Controller_data.c";
	this.html2Root["IR_Controller_data_c.html"] = "IR_Controller_data_c.html";
	this.html2SrcPath["rtwtypes_h.html"] = "../rtwtypes.h";
	this.html2Root["rtwtypes_h.html"] = "rtwtypes_h.html";
	this.html2SrcPath["rtmodel_h.html"] = "../rtmodel.h";
	this.html2Root["rtmodel_h.html"] = "rtmodel_h.html";
	this.getLink2Src = function (htmlFileName) {
		 if (this.html2SrcPath[htmlFileName])
			 return this.html2SrcPath[htmlFileName];
		 else
			 return null;
	}
	this.getLinkFromRoot = function (htmlFileName) {
		 if (this.html2Root[htmlFileName])
			 return this.html2Root[htmlFileName];
		 else
			 return null;
	}
}
Html2SrcLink.instance = new Html2SrcLink();
var fileList = [
"IR_Controller_c.html","IR_Controller_h.html","IR_Controller_private_h.html","IR_Controller_types_h.html","IR_Controller_data_c.html","rtwtypes_h.html","rtmodel_h.html"];
