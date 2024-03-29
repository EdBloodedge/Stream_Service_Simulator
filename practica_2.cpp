#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <fstream>  // Para ofstream


using namespace std;

class Nodo{

public:

  Nodo* pSig;
  string nombre, descripcion, categoria;

  virtual void Set(string nombre, string descripcion, string categoria);

  virtual void Agregar(string nombre, string descripcion, string categoria, int modo);
  virtual void Imprimir(int Modo);
  virtual void Buscar(string nombre);
  virtual void Modificar(string nombre);
  virtual void Eliminar(string nombre);

  virtual void Cargar(int pos);
  virtual void Guardar();

  Nodo();

};

/*class CContenido : public Nodo{

public:

  virtual void Set(string nombre, string descripcion, string categoria);

  virtual void Agregar(string nombre, string descripcion, string categoria, int modo);
  virtual void Imprimir(int Modo);
  virtual void Buscar(string nombre);
  virtual void Modificar(string nombre);
  virtual void Eliminar(string nombre);

  virtual void Cargar(int pos);
  virtual void Guardar();

};*/

class Lista{

private:
  Nodo* Inicio;
  int Modo;


public:

  bool IsEmpty();

  void Agregar();
  void Imprimir();
  void Buscar(string nombre);
  void Modificar(string nombre);
  void Eliminar(string nombre);

  Lista(int Modo);
  ~Lista();

};

class CPelicula : public Nodo{
  friend class Lista;

protected:
  virtual void Cargar(int pos);
  virtual void Guardar();

};

class CSerie : public Nodo{

  friend class Lista;

protected:
  virtual void Cargar(int pos);
  virtual void Guardar();

};

class CUsuario : public Nodo{

  friend class Lista;

protected:
  virtual void Cargar(int pos);
  virtual void Guardar();

};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(){

  int opc;
  int modo;

  string nombre;
  bool salir = false, subsalir;

  Lista Peliculas(1);
  Lista Series(2);
  Lista Usuarios(3);
  Lista* lista;

    do{

      subsalir = false;

      system("cls");
      cout<<"\n\n\t\t\t\t---------------------MENU----------------------\n\n";
      cout << "\n1. Peliculas";
      cout << "\n2. Series";
      cout << "\n3. Usuarios";
      cout << "\n4. Salir";

      cout<<"\nOpcion: ";
      fflush(stdin);
      cin>>modo;
      cout<<"\n\n ";

      opc = 0;

      switch (modo) {
        case 1:
          lista = &Peliculas;
          break;

        case 2:
          lista = &Series;
          break;

        case 3:
          lista = &Usuarios;
          break;

        case 4:
          salir = true;
          subsalir = true;
          break;

        default:
          "\n\nPor favor elija una opci\242n v\240lida.\n";
          system("pause");
      }

      while(!subsalir){

        system("cls");

          cout<<"\n\n\t\t\t\t---------------------MENU----------------------\n\n";

          cout<<"\n1. Agregar";
          cout<<"\n2. Imprimir";
          cout<<"\n3. Buscar";
          cout<<"\n4. Modificar";
          cout<<"\n5. Eliminar";
          cout<<"\n6. Regresar";
          cout<<"\nOpcion: ";
          fflush(stdin);
          cin>>opc;
          cout<<"\n\n ";


          switch(opc){
              case 1:
                  cout<<"\n\t\t\t------------------------AGREGAR-----------------------\n\n";
                  lista->Agregar();
                  break;

              case 2:
                  cout<<"\n\t\t\t------------------------IMPRIMIR-----------------------\n\n";
                  lista->Imprimir();
                  break;

              case 3:
                  cout<<"\n\t\t\t------------------------BUSCAR-----------------------\n\n";
                  cout << "Ingrese el nombre: ";
                  fflush(stdin);
                  getline(cin,nombre);
                  lista->Buscar(nombre);
                  break;

              case 4:
                  cout<<"\n\t\t\t------------------------MODIFICAR-----------------------\n\n";
                  cout << "Ingrese el nombre: ";
                  fflush(stdin);
                  getline(cin,nombre);
                  lista->Modificar(nombre);
                  break;

              case 5:
                  cout<<"\n\t\t\t------------------------ELIMINAR-----------------------\n\n";
                  cout << "Ingrese el nombre: ";
                  fflush(stdin);
                  getline(cin,nombre);
                  lista->Eliminar(nombre);
                  break;

              case 6:
                subsalir = true;
                break;

              default:
                "\n\nPor favor elija una opci\242n v\240lida.\n";
                system("pause");
          }

          system("pause");

      }

    }while(!salir);

    system("pause");
    return 0;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Nodo

void Nodo::Set(string nombre, string descripcion, string categoria){

  this->nombre = nombre;
  this->descripcion = descripcion;
  this->categoria = categoria;

  return;

}

void Nodo::Agregar(string nombre, string descripcion, string categoria, int modo){

  if(this->pSig == NULL){

    switch(modo){

      case 1:
        this->pSig = new CPelicula;
        break;

      case 2:
        this->pSig = new CSerie;
        break;

      case 3:
        this->pSig = new CUsuario;
        break;

    }
    this->pSig->Set(nombre, descripcion, categoria);

  }else{
    this->pSig->Agregar(nombre, descripcion, categoria, modo);
  }

  return;

}
void Nodo::Imprimir(int Modo){

  cout << nombre << endl << categoria << endl << descripcion << endl << "----------------" << endl;

  if(this->pSig != NULL && Modo == 1)
    this->pSig->Imprimir(1);

  return;

}
void Nodo::Buscar(string nombre){

  if(this->pSig == NULL){
    cout << "No se ha encontrado el nombre especificado";
    return;
  }

  if(this->pSig->nombre == nombre)
    this->pSig->Imprimir(0);
  else
    this->pSig->Buscar(nombre);

}
void Nodo::Modificar(string nombre){

  if(this->pSig == NULL){
    cout << "No se ha encontrado el nombre especificado";
    return;
  }

  if(this->pSig->nombre == nombre){

    string nNombre, nDescripcion, nCategoria;

    cout << "\nIngrese los datos actualizados:\nNombre: ";
    fflush(stdin);
    getline(cin,nNombre);
    cout << "\nDescripcion: ";
    fflush(stdin);
    getline(cin,nDescripcion);
    cout << "\nCategoria: ";
    fflush(stdin);
    getline(cin,nCategoria);

    this->pSig->Set(nNombre, nDescripcion, nCategoria);

    cout << "\n\nDatos actualizados correctamente.\n";

  }else{
    this->pSig->Modificar(nombre);
  }

  return;

}
void Nodo::Eliminar(string nombre){

  if(this->pSig == NULL){
    cout << "No se ha encontrado el nombre especificado";
    return;
  }

  if(this->pSig->nombre == nombre){

    Nodo* aux = this->pSig;

    this->pSig = this->pSig->pSig;
    delete aux;

  }else{
    this->pSig->Eliminar(nombre);
  }

  return;

}

void Nodo::Cargar(int pos){

  if(this->pSig != NULL)
    this->pSig->Cargar(0);

}
void Nodo::Guardar(){

  if(this->pSig != NULL)
    this->pSig->Guardar();

}

Nodo::Nodo(){

  this->pSig = NULL;

}

//Peliculas

void CPelicula::Cargar(int pos){

  ifstream f("pelis.txt");

  if(!f.is_open()){
    cout<<"Imposible abrir un archivo para cargar.";
    return;
  }

  f.seekg(pos, f.beg);

  char c;
  string nombre, descripcion, categoria;

  f.get(c);

  if(f.eof()){
    f.close();
    return;
  }

  f.unget();

  for(int i = 0; i<3; i++){
    f.get(c);
    while( c != '|' && c != '*'){

      switch (i) {
        case 0:
          nombre += c;
          break;

        case 1:
          descripcion += c;\
          break;

        case 2:
          categoria += c;
          break;
      }

      f.get(c);
    }
  }

  this->Agregar(nombre, descripcion, categoria, 1);

  pos = f.tellg();
  f.get(c);

  if(!f.eof()){
    f.close();
    this->pSig->Cargar(pos);
  }
  f.close();

}
void CPelicula::Guardar(){

  ofstream f("pelis.txt", ofstream::app);

  if(!f.is_open()){
    cout<<"Imposible abrir un archivo para cargar.";
    return;
  }

  string tnombre, tdescripcion, tcategoria;
  const char* pNombre, *pDescripcion, *pCategoria;

  if(this->pSig != NULL){

    tnombre = this->pSig->nombre;
    tdescripcion = this->pSig->descripcion;               // Copia los atributos en strings
    tcategoria = this->pSig->categoria;

    pNombre = tnombre.c_str();
    pDescripcion = tdescripcion.c_str();                 // Guarda los datos
    pCategoria = tcategoria.c_str();

    f.write(pNombre, tnombre.length());
    f.put('|');
    f.write(pDescripcion, tdescripcion.length());
    f.put('|');
    f.write(pCategoria, tcategoria.length());
    f.put('*');

    f.close();

    this->pSig->Guardar();

  }
  return;

}

//Series

void CSerie::Cargar(int pos){
  ifstream f("series.txt");

  if(!f.is_open()){
    cout<<"Imposible abrir un archivo para cargar.";
    return;
  }

  f.seekg(pos, f.beg);

  char c;
  string nombre, descripcion, categoria;
  int tam;

  f.get(c);

  if(f.eof()){
    f.close();
    return;
  }

  f.unget();

  for(int i=0; i<3; i++){         //Un for para cambiar entre los tres atributos

    f.get(c);                 //Lee el caracter de tamano y lo interpreta como numero
    tam = c;

    for(int j=0; j<tam; j++){      //Desde cero, hasta el tamano indicado....

      f.get(c);                   //Obtiene caracteres, y los va almacenando en el atributo correspondiente

      if(i == 0)
        nombre += c;

      if(i == 1)
        descripcion += c;

      if(i == 2)
        categoria += c;

    }
  }

  this->Agregar(nombre, descripcion, categoria, 2);

  pos = f.tellg();
  f.get(c);

  if(!f.eof()){
    f.close();
    this->pSig->Cargar(pos);
  }
  f.close();

}
void CSerie::Guardar(){

  ofstream f("series.txt", ofstream::app);

  if(!f.is_open()){
    cout<<"Imposible abrir un archivo para cargar.";
    return;
  }

  string tnombre, tdescripcion, tcategoria, lNombre, lDescripcion, lCategoria;
  char n, d, c;
  const char* pNombre, *pDescripcion, *pCategoria;

  if(this->pSig != NULL){

    tnombre = this->pSig->nombre;
    tdescripcion = this->pSig->descripcion;  //Guarda los atributos en strings
    tcategoria = this->pSig->categoria;

    n = tnombre.length();
    d = tdescripcion.length();              //Guarda el tamano de los strings como un caracter
    c = tcategoria.length();

    lNombre = n + tnombre;
    lDescripcion = d + tdescripcion;        //Junta tamano con su respectiva cadena
    lCategoria = c + tcategoria;

    pNombre = lNombre.c_str();
    pDescripcion = lDescripcion.c_str();   //Convierte cada una en una cadena constante, para usar fputs
    pCategoria = lCategoria.c_str();

    f.write(pNombre, lNombre.length());
    f.write(pDescripcion, lDescripcion.length());                 //Guarda los datos en el archivo
    f.write(pCategoria, lCategoria.length());

    f.close();

    this->pSig->Guardar();

  }
  return;

}

//Usuarios

void CUsuario::Cargar(int pos){

  ifstream f("usuarios.txt"); //se abre el archivo

  if(!f.is_open()){
    cout<<"Imposible abrir un archivo para cargar.";
    return;
  }

  f.seekg(pos, f.beg); //se busca la posicion en la que se quedo el anterior nodo

  char c;
  string nombre, descripcion, categoria;

  f.get(c); //se obtiene un caracter para checar si estamos en el fin del archivo

  if(f.eof()){
    f.close(); //Lo cierra si es que es asi
    return;
  }

  f.unget();  //Regresa el caracter tomado, para iniciar bien el proceso

  for(int i = 0; i<3; i++){ //Para cada uno de los tres campos..
    f.get(c);
    for(int j = 0; j<20; j++){//Ya que los registros son de 20 espacios, durante 20 ciclos

      switch (i) { //Se agrega el caracter al campo correspondiente
        case 0:
          nombre += c;
          break;

        case 1:
          descripcion += c;\
          break;

        case 2:
          categoria += c;
          break;
      }

      f.get(c); //Y se toma un caracter para continuar con el proceso
    }
  }

  this->Agregar(nombre, descripcion, categoria, 3);  //Finalmente se agrega el nodo

  pos = f.tellg();      //Se toma la posicion en la que se quedo el archivo
  f.get(c);             //Se busca si es fin de archivo

  if(!f.eof()){
    this->pSig->Cargar(pos);  //Si no lo es, se avanza para cargar otro nodo
    f.close();  //Y se cierra el archivo.
  }

}
void CUsuario::Guardar(){

  ofstream f("usuarios.txt", ofstream::app);

  if(!f.is_open()){
    cout<<"Imposible abrir un archivo para cargar.";
    return;
  }

  string tnombre, tdescripcion, tcategoria;
  const char* pNombre, *pDescripcion, *pCategoria;
  int largo;

  if(this->pSig != NULL){

    tnombre = this->pSig->nombre;
    tdescripcion = this->pSig->descripcion;               // Copia los atributos en strings
    tcategoria = this->pSig->categoria;

    pNombre = tnombre.c_str();
    pDescripcion = tdescripcion.c_str();                 // Guarda los datos
    pCategoria = tcategoria.c_str();

    f.write(pNombre, tnombre.length());                 //Se guarda el atributo
    largo = 20-tnombre.length();                    //Se obtiene un 'largo' que es el espacio faltante para que el nodo consiga tener un espacio de 20
    for(int j = 0; j <= largo; j++)
      f.put(' ');                       //Y se agrega un espacio en blanco por cada uno de estos espacios faltantes, asi el registro tiene siempre longitud fija de 20

    f.write(pDescripcion, tdescripcion.length());
    largo = 20-tdescripcion.length();
    for(int j = 0; j <= largo; j++)
      f.put(' ');

    f.write(pCategoria, tcategoria.length());
    largo = 20-tcategoria.length();
    for(int j = 0; j <= largo; j++)
      f.put(' ');

    f.close();              //Se cierra el archivo.

    this->pSig->Guardar(); //Y se llama a guardar al nodo siguiente.

  }
  return;

}

//Lista

bool Lista::IsEmpty(){

  if(Inicio->pSig == NULL)
    return true;

  return false;
}

void Lista::Agregar(){

  string nombre, descripcion, categoria;

  cout << "Ingrese los datos.\nNombre: ";
  fflush(stdin);
  getline(cin,nombre);
  cout << "\nDescripcion: ";
  fflush(stdin);
  getline(cin,descripcion);
  cout << "\nCategoria: ";
  fflush(stdin);
  getline(cin,categoria);

  Inicio->Agregar(nombre, descripcion, categoria, Modo);

  return;
}
void Lista::Imprimir(){

  if(this->IsEmpty()){
    cout << "No existen elementos.";
    return;
  }

  Inicio->pSig->Imprimir(1);

}
void Lista::Buscar(string nombre){

  if(this->IsEmpty()){
    cout << "No existen elementos.";
    return;
  }

  Inicio->Buscar(nombre);

}
void Lista::Modificar(string nombre){

  if(this->IsEmpty()){
    cout << "No existen elementos.";
    return;
  }

  Inicio->Modificar(nombre);

}
void Lista::Eliminar(string nombre){

  if(this->IsEmpty()){
    cout << "No existen elementos.";
    return;
  }

  Inicio->Eliminar(nombre);

}

Lista::Lista(int Modo){

  this->Modo = Modo;

  switch (Modo) {
    case 1:
      this->Inicio = new CPelicula;
      break;

    case 2:
      this->Inicio = new CSerie;
      break;

    case 3:
      this->Inicio = new CUsuario;
      break;
  }

  this->Inicio->Cargar(0);

}
Lista::~Lista(){

  ofstream f;

  switch (this->Modo) {
    case 1:
       f.open("pelis.txt", ofstream::trunc);
      break;

    case 2:
      f.open("series.txt", ofstream::trunc);
      break;

    case 3:
      f.open("usuarios.txt", ofstream::trunc);
      break;
  }

  f.close();
  Inicio->Guardar();

}
