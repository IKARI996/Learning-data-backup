// �û��� Customer����
#ifndef CUSTOMER_H_
#define CUSTOMER_H_

class Customer
{
	public:
		// ���õ���ʱ��
		void setArrivalTime(int arrives) 
		{arrivalTime = arrives; }
		// ��������ʱ��
		int getArrivalTime() const {return arrivalTime;}
		// ������ȥʱ��
		void setDepartureTime(int departs) 
		{departureTime = departs;}
		// ����ܹ����ѵ�ʱ��
		int totalTime() 
		{return departureTime - arrivalTime;}
	private:
		int arrivalTime, departureTime;
};
#endif
