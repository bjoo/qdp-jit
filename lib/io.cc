// $Id: io.cc,v 1.10 2003-04-20 04:03:34 edwards Exp $
//
// QDP data parallel interface
//

#include "qdp.h"

QDP_BEGIN_NAMESPACE(QDP);

//-----------------------------------------
//! text reader support
TextReader::TextReader() {iop=false;}

TextReader::TextReader(const char* p) {open(p);}

void TextReader::open(const char* p) 
{
  if (Layout::primaryNode())
  {
    f.open(p);

    if (! f.is_open())
      QDP_error_exit("failed to open file %s",p);
  }

  iop=true;
}

void TextReader::close()
{
  if (is_open()) 
  {
    if (Layout::primaryNode()) 
      f.close();
    iop = false;
  }
}

bool TextReader::is_open() {return iop;}

TextReader::~TextReader() {close();}


//-----------------------------------------
//! text writer support
TextWriter::TextWriter() {iop=false;}

TextWriter::TextWriter(const char* p) {open(p);}

void TextWriter::open(const char* p)
{
  if (Layout::primaryNode()) 
    f.open(p,std::ofstream::out);

  iop=true;
}

void TextWriter::close()
{
  if (is_open()) 
  {
    if (Layout::primaryNode()) 
      f.close();
    iop = false;
  }
}

bool TextWriter::is_open() {return iop;}

TextWriter::~TextWriter() {close();}


//-----------------------------------------
//! text reader support
NmlReader::NmlReader() {abs = NULL;iop=false;}

NmlReader::NmlReader(const char* p) {open(p);}

void NmlReader::open(const char* p)
{
  abs = NULL;

  // Make a barrier call ?

  if (Layout::primaryNode()) 
  {
    FILE *f;

    if ((f = fopen(p,"rb")) == NULL)
      QDP_error_exit("NmlReader: error opening file %s",p);
    
    if ((abs = new_abstract("abstract")) == NULL)   // create a parse tree
      QDP_error_exit("NmlReader: Error initializing file - %s - for reading",p);
    
    // Parse from file
    if (param_scan_file(abs, f) != 0)
      QDP_error_exit("NmlReader: Error scaning namelist file - %s - for reading",p);

    fclose(f);

    init_nml_section_stack(abs);

    fprintf(stderr,"Section dump\n");
    print_section(stderr, abs);
  }

  // Make a barrier call ?

  iop=true;
}

void NmlReader::close()
{
  if (iop)
  {
    if (Layout::primaryNode()) 
      rm_abstract(abs);

    iop = false;
  }
}

bool NmlReader::is_open() {return iop;}

NmlReader::~NmlReader() {close();}


//! Push a namelist group 
NmlReader& push(NmlReader& nml, const string& s)
{
  if (Layout::primaryNode()) 
    push_nml_section_stack(s.c_str());

  return nml;
}

//! Pop a namelist group
NmlReader& pop(NmlReader& nml)
{
  if (Layout::primaryNode()) 
    pop_nml_section_stack();

  return nml;
}


//! Function overload read of  Integer
NmlReader& read(NmlReader& nml, const string& s, Integer& d)
{
  WordType<Integer>::Type_t  dd;
  read(nml,s,dd);
  d = dd;

  return nml;
}

//! Function overload read of  Real
NmlReader& read(NmlReader& nml, const string& s, Real& d)
{
  WordType<Real>::Type_t  dd;
  read(nml,s,dd);
  d = dd;

  return nml;
}

//! Function overload read of  Double
NmlReader& read(NmlReader& nml, const string& s, Double& d)
{
  WordType<Double>::Type_t  dd;
  read(nml,s,dd);
  d = dd;

  return nml;
}


//-----------------------------------------
//! namelist writer support
NmlWriter::NmlWriter() {iop=false;}

NmlWriter::NmlWriter(const char* p) {open(p);}

void NmlWriter::open(const char* p)
{
  if (Layout::primaryNode()) 
    f.open(p,std::ios_base::out);
  iop=true;

  push(*this,"FILE");  // Always start a file with this group
}

void NmlWriter::close()
{
  if (iop) 
  {
    pop(*this);  // Write final end of file group

    if (Layout::primaryNode()) 
      f.close();
    iop = false;
  }
}

bool NmlWriter::is_open() {return iop;}

NmlWriter::~NmlWriter() {close();}

//! Push a namelist group 
NmlWriter& push(NmlWriter& nml, const string& s)
{
  if (Layout::primaryNode()) 
    nml.get() << "&" << s << endl; 

  return nml;
}

//! Pop a namelist group
NmlWriter& pop(NmlWriter& nml)
{
  if (Layout::primaryNode()) 
    nml.get() << "&END\n"; 

  return nml;
}

//! Write a comment
NmlWriter& operator<<(NmlWriter& nml, const char* s)
{
  if (Layout::primaryNode()) 
    nml.get() << "! " << s << endl; 

  return nml;
}



//-----------------------------------------
//! Binary reader support
BinaryReader::BinaryReader() {iop=false; f = NULL;}

BinaryReader::BinaryReader(const char* p) {open(p);}

void BinaryReader::open(const char* p) 
{
  if (Layout::primaryNode()) 
  {
    if ((f = fopen(p,"rb")) == NULL)
      QDP_error_exit("BinaryReader: error opening file %s",p);
  }

  iop = true;
}

void BinaryReader::close()
{
  if (iop)
  {
    if (Layout::primaryNode()) 
      fclose(f);

    iop = false;
  }
}


bool BinaryReader::is_open() {return iop;}

BinaryReader::~BinaryReader() {close();}



//-----------------------------------------
//! Binary writer support
BinaryWriter::BinaryWriter() {iop=false; f = NULL;}

BinaryWriter::BinaryWriter(const char* p) {open(p);}

void BinaryWriter::open(const char* p) 
{
  if (Layout::primaryNode()) 
  {
    if ((f = fopen(p,"wb")) == NULL)
    {
      cerr << "BinaryWriter: error opening file: " << p << endl;
      QDP_error_exit("BinaryWriter: error opening file %s",p);
    }
  }

  iop = true;
}

void BinaryWriter::close()
{
  if (iop)
  {
    if (Layout::primaryNode()) 
      fclose(f);

    iop = false;
  }
}


bool BinaryWriter::is_open() {return iop;}

BinaryWriter::~BinaryWriter() {close();}



QDP_END_NAMESPACE();
