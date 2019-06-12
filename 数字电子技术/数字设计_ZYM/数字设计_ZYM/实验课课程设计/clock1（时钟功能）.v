//1. `timescale 1ns / 1ps������Ϊ��ʱ�ӵ�λΪ1ns��ʱ�Ӿ���Ϊ1ps��
//2. �ڱ�������У�`timescale��Ӱ�����������ģ���е�ʱ��ֵ��ֱ��������һ��
//`timescaleָ���`resetallָ�
//3. ��һ������еĶ��ģ����������`timescale����ָ��ʱ��ģ��������λ
//������ģ�����Сʱ�Ӿ����ϣ���������ʱ�Ӷ���Ӧ�ػ���Ϊ��Сʱ�Ӿ��ȡ�

`timescale 1ns / 1ps

//ʱ�ӷ�Ƶ�� 
//������Ƶ�ʵ�λ������ʱ�䵥λ��Ƶ�ʷ�֮һ��ʱ�䣬���Ժ���=1/�� 
module clkdiv (
input wire clk,
 input wire clr, 
 output wire clk190,
  output wire clk01); 
  reg [40:0] q; // 41 λ������ 
  always @ (posedge clk or posedge clr)
   begin 
   if (clr==1)      
      q <= 0;
       else      
          q <= q + 1;
   end 
assign clk190 = q[17];  // 190 Hz ��������ܵ�ɨ����ʾ 
assign  clk01=q[25];// 1.5 Hz
 endmodule

//�������ʾģ��,��ʱ�ֵ�������л� 
//bug������
module x7seg_msg( 
        input wire [3:0]second1,//��λ�룬��ʾ�����������9 
         input wire [3:0]second2,//ʮλ�룬��ʾ�����������5 
          input wire [3:0]minute1,//��λ�֣���ʾ�����������9  
           input wire [3:0]minute2,//��λ�֣���ʾ�����������5 
           input wire[3:0]hour1,//��λʱ����ʾ�����������3
           input wire[3:0]hour2,//ʮλʱ����ʾ�����������2 
            input wire clk190,
            input wire clr,
            input wire change,//ʱ�ֵ�������л� 
             output reg [6:0] a_to_g,//�߶ι� 
             output reg [3:0] an ); //�Ŀ���ʾ���ֱ���ʾ������ 
             reg [1:0] s;
              reg [3:0] digit;
              wire [3:0] aen;
              assign aen = 4'b1111; 
	//һ����λ����ܣ�ÿһλ��ʾʲô����
          always @ (* ) 
           case (s) 
           0://��������λ(���ң� 
            begin
                if(change) 
                    digit=minute1;
            else
                  digit = second1;
             end
           1:
		    begin
                if(change)
                    digit=minute2;
              else
                     digit = second2;
              end
           2:   
		   begin
               if(change)
                   digit=hour1;
               else
                    digit = minute1;  
                end  
           3://��������λ(����  
		   begin
               if(change)
                   digit=hour2;
                else
                     digit = minute2;    
            end
           endcase
	//����digit��ʾ��������ʲô
       always @ ( * )
           case (digit)     
           0: a_to_g = 7'b0000001;     
           1: a_to_g = 7'b1001111;  
           2: a_to_g = 7'b0010010;    
           3: a_to_g = 7'b0000110; 
           4: a_to_g = 7'b1001100;     
           5: a_to_g = 7'b0100100;     
           6: a_to_g = 7'b0100000;     
           7: a_to_g = 7'b0001111; 
           8: a_to_g = 7'b0000000; 
           9: a_to_g = 7'b0000100;    
           default: a_to_g = 7'b0000001;//��ʾ0��  
           endcase
	
      always @ (posedge clk190 or posedge clr)
       begin      
           if (clr ==1) //����
           begin    
               s <= 0;
           end  
           else      //ÿ��190HZ��Ƶ��������ѡ������һյ��
               s<=s+1;
        end 
        
        //ȷ��ÿ��������϶�����ʾ����
            always @ ( *) 
                 begin      
                   an = 4'b1111; //��������ȫ������
                    if (aen[s] == 1)   //������һλ��      
                    an[s] = 0; 
                     if(clr==1)
                     an = 4'b1111;  
                 end 
    endmodule 


//����ģ��
module scroll_top(
        input wire clk,
        input wire btn,
        input wire add_h1,//��������ʱ�ӣ� 
        input wire add_m1,//�����������ӣ� 
        input wire change1,//����ʵ��ʱ�ֵ�������л��� 
        output wire[3:0]an,
        output wire[6:0]a_to_g);
        
        wire clk1,clkl190,clr,change,add_m,add_h;
        assign clr=btn;//���� 
        assign change=change1;
        assign add_m=add_m1;
        assign add_h=add_h1;
        reg[3:0]second1,second2,minute1,minute2,hour1,hour2;
   	
	//���÷�Ƶ��ʾģ��
	clkdiv U(.clk(clk),
             .clr(clr),
             .clk190(clk190),
             .clk01(clk1));         
           always @(posedge clk1 )
                begin
                       second1=second1+1;
                    
			//����
			if(clr==1)
                            begin
                              second1=4'b0000;
                              second2=4'b0000;
                              minute1=4'b0000;
                              minute2=4'b0000;
                              hour1=4'b0000;
                              hour2=4'b0000;
                        end
			//����ʱ�䣬������ʱ�Ӻͷ��� 
                        if(add_h)
                            hour1=hour1+1;
                        if(add_m)
                            minute1=minute1+1;
                    if(second1==4'b1010)
                        begin
                            second2=second2+1;
                            second1=4'b0000;
                         end
                    if(second2==4'b0110)
                        begin
                            minute1=minute1+1;
                            second2=4'b0000;
                            end
                         if(minute1==4'b1010)
                            begin
                                minute2=minute2+1;
                                minute1=4'b0000;
                                end
                         if(minute2==4'b0110)
                            begin
                            hour1=hour1+1;
                            minute2=4'b0000;
                            end
                          if(hour1==4'b1010)
                            begin
                            hour2=hour2+1;
                            hour1=4'b0000;
                            end
                            if(hour2==4'b0010&&hour1==4'b0100)
                                begin
                                    hour1=4'b0000;
                                    hour2=4'b0000;
                                 end
             end  
		//��ʾ����             
              x7seg_msg   R(.second1(second1),  
                            .second2(second2),
                            .minute1(minute1),
                            .minute2(minute2),
                            .hour1(hour1),
                            .hour2(hour2),
                            .clk190(clk190),
                            .clr(clr),
                            .change(change),
                            .a_to_g(a_to_g),
                            .an(an));
 endmodule                                   
