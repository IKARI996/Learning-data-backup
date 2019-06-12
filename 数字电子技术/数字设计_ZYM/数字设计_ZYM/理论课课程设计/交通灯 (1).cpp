module traffic_light(
    input clock, reset, parade,// 1 Hzʱ���źţ�ͬ����λ , paradeΪ �����ź� 
	output[5:0] lamp_a1, lamp_a2, lamp_b1, lamp_b2,// �����źŵ� 
	output[7:0] count_a1, count_a2, count_b1, count_b2// ����ʱ�� 
    );
reg[5:0] lamp_a, lamp_b; // ��ת�̣���ת�ƣ���ת�죬ֱ�к죬ֱ�лƣ�ֱ����
reg[7:0] num_a, num_b; // �ڲ�����ʱ
reg temp_a, temp_b; // ״̬�ͼ���ת���ź�
reg[2:0] state_a, state_b; // a��b��״̬�Ĵ���
reg[7:0] red_a, yellow_a, green_a, left_a, red_b, yellow_b, green_b, left_b;
assign count_a1 = num_a, count_a2 = num_a;
assign count_b1 = num_b, count_b2 = num_b;
assign lamp_a1 = lamp_a, lamp_a2 = lamp_a;
assign lamp_b1 = lamp_b, lamp_b2 = lamp_b;




always@(posedge clock)
begin
    if( !reset )// ��λ�ź��ڵ͵�ƽʱ��������ʱһ�и�λ 
    begin
        green_a <= 8'd40; // a�� ͨ�� 40s
        yellow_a <= 8'd5; // a�� ��ת׼�� 5s , a�� ��ֹͨ��׼�� 5s 
        left_a <= 8'd15; // a�� ��ת 15s
        red_a <= 8'd55; // a�� ��ֹͨ�� 55s
        
        red_b <= 8'd65; // b�� ��ֹͨ�� 65s
        green_b = 8'd30; // b�� ͨ�� 30s 
        yellow_b <= 8'd5; // b �� ��ת׼�� 5s , b�� ��ֹͨ��׼�� 5s 
        left_b <= 8'd15; //  b�� ��ת 15s
        
        lamp_a <= 'b000000; //  ��ת�̣���ת�ƣ���ת�죬ֱ�к죬ֱ�лƣ�ֱ����  ������
        state_a <= 'b000; // 0״̬
        temp_a <=  0; // ״̬�ͼ���ת���ź�
        num_a <= 0; // �ڲ�����ʱ
    end
    // reset == 1,����������  
    else
    begin
    	if( !parade )// parade == 0��������״̬����ͨ����������
		begin 
	        //�� temp_a == 0 ʱ��״̬�任
	        if( !temp_a )
	        begin
	            temp_a <= 1;
	            case( state_a )
	                 // a�� ͨ�� 
	                'b000:
	                 begin
	                    num_a <= green_a;// �ڲ�����ʱ ���� �̵Ƶĵ���ʱ
	                    lamp_a <= 'b001001; //  ��ת��,ֱ���� ��
	                    state_a <= 'b001; //  ��green_a��40s����ʱ��0sʱ��temp_a==0,��ɽ����жϣ���Ϊ��һ��״̬
	                 end 
	                 'b001:
	                 begin
	                     num_a <= yellow_a;// �ڲ�����ʱ ���� �ƵƵĵ���ʱ
	                    lamp_a <= 'b010010; //  ֱ�лƣ���ת�� ��
	                    state_a <= 'b010; //  ��yellow_a��5s����ʱ��0sʱ��temp_a==0,��ɽ����жϣ���Ϊ��һ��״̬
	                 end 
	                 'b010:
	                 begin
	                     num_a <= left_a;// �ڲ�����ʱ ���� ��ת�Ƶĵ���ʱ
	                    lamp_a <= 'b100100; //  ��ת��,ֱ�к� ��
	                    state_a <= 'b011; //  ��left_a��15s����ʱ��0sʱ��temp_a==0,��ɽ����жϣ���Ϊ��һ��״̬
	                 end 
	                 'b011:
	                 begin
	                     num_a <= yellow_a;// �ڲ�����ʱ ���� �ƵƵĵ���ʱ
	                    lamp_a <= 'b010100; //  ��ת�ƣ�ֱ�к� ��
	                    state_a <= 'b100; //  ��yellow_a��5s����ʱ��0sʱ��temp_a==0,��ɽ����жϣ���Ϊ��һ��״̬
	                 end 
	                 'b100:
	                 begin
	                     num_a <= red_a;// �ڲ�����ʱ ���� ��Ƶĵ���ʱ
	                    lamp_a <= 'b001100; //  ��ת��,ֱ���� ��
	                    state_a <= 'b000; //  ��green_a��40s����ʱ��0sʱ��temp_a==0,��ɽ����жϣ���Ϊ��һ��״̬
	                 end 
	                 default: lamp_a <= 'b000000;
	            endcase
	        end 
	        // �� temp_a == 1 ʱ��״̬���任
	        else
	        begin
	            if(num_a > 1)
	            begin
	                if(num_a[3:0] == 0)
	                begin
	                    num_a[3:0] <= 'b1111;
	                    num_a[7:4] <= num_a[7:4] - 1;
	                end
	                else
	                    num_a[3:0] <= num_a[3:0] - 1;
	                // num_a = num_a - 1;
	            end
	            if(num_a == 2)// �¸�clock����ʱ��num_a Ϊ 1��Ȼ���Ϊ��һ��״̬ 
	                temp_a <= 0;
	        end
	    else  // parade == 1��a������״̬��һֱ�� a��ֱ���̵ƣ�b���� 
	    begin
	    	num_a <= green_a;// �ڲ�����ʱ ���� �̵Ƶĵ���ʱ
	        lamp_a <= 'b001001;
		end    
	        
	end
end

always@(posedge clock)
begin
    if( !reset ) 
    begin
        lamp_b <= 'b000000; //  ��ת�̣���ת�ƣ���ת�죬ֱ�к죬ֱ�лƣ�ֱ����  ������
        state_b <= 'b000; // 0״̬
        temp_b <=  0; // ״̬�ͼ���ת���ź�
        num_b <= 0; // �ڲ�����ʱ
    end
    // reset == 1,����������  
    else
    begin
    	if( !parade )
    	begin
	        //�� temp_b == 0 ʱ��״̬�任
	        if( !temp_b )
	        begin
	            temp_b <= 1;
	            case( state_b )
	                 // b�� ��ֹ 
	                'b000:
	                 begin
	                    num_b <= red_b;
	                    lamp_b <= 'b001100; 
	                    state_b <= 'b001; 
	                 end 
	                 'b001:
	                 begin
	                     num_b <= green_b;
	                    lamp_b <= 'b001001; 
	                    state_b <= 'b010; 
	                 end 
	                 'b010:
	                 begin
	                     num_b <= yellow_b;
	                    lamp_b <= 'b010010; 
	                    state_b <= 'b011; 
	                 end 
	                 'b011:
	                 begin
	                     num_b <= left_b;
	                    lamp_b <= 'b100100;
	                    state_b <= 'b100;
	                 end 
	                 'b100:
	                 begin
	                     num_b <= yellow_b;
	                    lamp_b <= 'b010100;
	                    state_b <= 'b000;
	                 end 
	                 default: lamp_b <= 'b000000;
	            endcase
	        end 
	        else
	        begin
	            if(num_b > 1)
	            begin
	                if(num_b[3:0] == 0)
	                begin
	                    num_b[3:0] <= 'b1111;
	                    num_b[7:4] <= num_b[7:4] - 1;
	                end
	                else
	                    num_b[3:0] <= num_b[3:0] - 1;
	            end
	            if(num_b == 2)
	                temp_b <= 0;
	        end
	    else // ����״̬��b�����
		begin
			num_b <= red_b;
	        lamp_b <= 'b001100; 
		end 
    end
end
endmodule





`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/12/24 12:30:50
// Design Name: 
// Module Name: simu
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


module simu(
);
// testbench ʱ���ź�
reg clk = 0;
//always #500000000 clk <= ~clk;
always #0.5 clk <= ~clk;
// ����testģ��
reg reset = 0;
always #120 reset <= ~reset;

wire[5:0] lamp_a1, lamp_a2, lamp_b1, lamp_b2;// �����źŵ� 
wire[7:0] count_a1, count_a2, count_b1, count_b2;// ����ʱ��
traffic_light mytraffic_light( clk, reset,// 1 Hzʱ���źţ�ͬ����λ
	 lamp_a1, lamp_a2, lamp_b1, lamp_b2,// �����źŵ� 
	 count_a1, count_a2, count_b1, count_b2// ����ʱ�� 
    );

endmodule





