/***************************************************
Materia:	Gráficas Computacionales
Tarea:	    6 - Isosuperficies
Fecha:		8 de octubre del 2012
Autor:      Marco Chavez
***************************************************/

class Punto {

	public:
		Punto(float nuevaX, float nuevaY, float nuevaZ, int nuevaR, int nuevaG, int nuevaB, float nuevaVx, float nuevaVy);
		Punto();
		~Punto(void);

		float getX();
		float getY();
		float getZ();
		void setXYZ(float nuevaX, float nuevaY, float nuevaZ);

		int getR();
		int getG();
		int getB();
		void setColor(int nuevaR, int nuevaG, int nuevaB);

		float getVx();
		float getVy();
		void setVx(float nuevaVx);
		void setVy(float nuevaVy);

		void setFixed(bool nFixed);
		bool isFixed();


	private:
		float x;
		float y;
		float z;
		int r;
		int g;
		int b;
		float vx;
		float vy;
		bool fixed;
};

