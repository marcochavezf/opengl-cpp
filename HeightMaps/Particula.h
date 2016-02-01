/***************************************************
Materia:	Gráficas Computacionales
Tarea:	    7 - la Telota
Fecha:		22 de octubre del 2012
Autor:      Marco Chavez
***************************************************/
class Particula{
	public:
		Particula(float x, float y, float z);
		Particula(int id, float* posicion);
		Particula();
		~Particula(void);

		int getID();

		void calcularColor();
		unsigned char* getColor();

		float* getPosicion();
		float* getPosAnt();
		void setPosicion(float* posicion);

		float* getVelocidad();
		void setVelocidad(float* velocidad);

		float* getFuerza();
		void addFuerza(float* fuerza);
		void clearForce();

		bool getFixed();
		void setFixed(bool b);

		void Verlet(float dt);

		void addNormal(float* n);
		float* getVectorUnitario();
		void clearNormal();

	private:
		int id;

		unsigned char color[3];

		float posicion[3];
		float posAnterior[3];

		float normal[3];
		int totalNormales;

		float velocidad[3];

		float fuerza[3];
		float masa;

		bool fixed;
};