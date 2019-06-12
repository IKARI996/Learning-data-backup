`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/14/2014 04:18:01 PM
// Design Name: 
// Module Name: xadc_top
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module xadc_top(
input clk100,RESET,
output [15:0] temp,
output [11:0] seg,
input[2:0] sw,
input A_VAUXP,A_VAUXN,B_VAUXP,B_VAUXN//A_VAUX is from  JXADC3,B_VAUX is from  JXADC1
    );

    wire DCLK;
    wire[15:0]MEASURED_TEMP,MEASURED_VCCINT,MEASURED_VCCAUX,MEASURED_VCCBRAM,MEASURED_AUX_A,MEASURED_AUX_B;
    wire[15:0]MEASURED_AUX;
    clk_wiz_0 u_clk(
    .clk_in1(clk100),
    .clk_out1(DCLK)
    );
    
    ug480 u_xadc(
       . DCLK(DCLK),
     .RESET(RESET),
    .VAUXP({A_VAUXP,B_VAUXP,2'b00}),
    . VAUXN({A_VAUXN,B_VAUXN,2'b00}),  // Auxiliary analog channel inputs
    .VP(), 
    .VN(),// Dedicated and Hardwired Analog Input Pair
     
     .MEASURED_TEMP(MEASURED_TEMP), 
     .MEASURED_VCCINT(MEASURED_VCCINT),  
     .MEASURED_VCCAUX(MEASURED_VCCAUX), 
     .MEASURED_VCCBRAM(MEASURED_VCCBRAM), 
     .MEASURED_AUX0(), 
     .MEASURED_AUX1(), 
     .MEASURED_AUX2(MEASURED_AUX_B), 
     . MEASURED_AUX3(MEASURED_AUX_A), 
 
     . ALM(), 
     .CHANNEL(),       
     . OT(), 
     .EOC(), 
     . EOS()
    );
    /*****calculate the  Units,decimal1 ,decimal2,decimal3
     for example,if MEASURED_AUX[15:4] is 12'hE3E,
     then the voltage is 0.890V,Units is 0,decimal1 is 8,decimal2 is 9,decimal3 is 0.****/
    wire[3:0] Units,decimal1 ,decimal2,decimal3;
    assign Units = MEASURED_AUX[15:4]/4096;
     assign decimal1 = MEASURED_AUX[15:4]*10/4096;
     assign decimal2 = (MEASURED_AUX[15:4]*10 - (MEASURED_AUX[15:4]*10/4096*4096))*10/4096;
      assign decimal3 = (MEASURED_AUX[15:4]*100 - (MEASURED_AUX[15:4]*10/4096)*4096*10 - ( (MEASURED_AUX[15:4]*10 - (MEASURED_AUX[15:4]*10/4096*4096))*10/4096)*4096)*10/4096;
 
  //segment display
    smg_disp u_seg_disp(
    .clk50mhz(DCLK),
    .keycount({Units,decimal1,decimal2,decimal3}),
    .ledouta(seg)
    );
//    always@(*)begin
//    case (sw )
//    3'b000: temp = MEASURED_TEMP;
//    3'b001:temp = MEASURED_VCCINT;
//    3'b010:temp = MEASURED_VCCAUX;
//    3'b011:temp = MEASURED_VCCBRAM;
//    3'b100: temp = MEASURED_AUX_A;
//     3'b101: temp = MEASURED_AUX_B;
//   default: temp =16'b0;
//    endcase
//    end
assign MEASURED_AUX = sw[0]==1? MEASURED_AUX_A:MEASURED_AUX_B;
  assign temp ={ MEASURED_AUX};
endmodule
