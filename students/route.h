#ifndef __ROUTE_H_
#define __ROUTE_H_

typedef struct{
	char a,b;
	int row;
}ConnectionCursor;

class Route {
private:
	signed long _value;
	std::vector<ConnectionCursor> _n;
	public:
	Route(){
		_value = 0;
		}	

	std::vector<ConnectionCursor> getConnections(){
		return _n;
	}

	void SetValue(signed int value){
		_value = value;
	}

	void AddConnection(int a, int b, int row){
		ConnectionCursor c;
		c.a=a;
		c.b=b;
		c.row=row;
		_n.push_back(c);
	}
};

#endif