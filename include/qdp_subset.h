// -*- C++ -*-
/*! @file
 * @brief Sets and subsets
 */

#ifndef QDP_SUBSET_H
#define QDP_SUBSET_H

namespace QDP {

/*! @defgroup subsets Sets and Subsets
 *
 * Sets are the objects that facilitate colorings of the lattice.
 * Subsets are groups of sites that are all of one color.
 * Subsets (and in a few cases Sets) can be used to restrict operations
 * to only a particular coloring of the lattice.
 *
 * @{
 */

//-----------------------------------------------------------------------
//! SetMap
class SetFunc
{
public:
  // Virtual destructor to stop compiler warnings - no cleanup needed
  virtual ~SetFunc() {}
  virtual int operator() (const multi1d<int>& coordinate) const = 0;
  virtual int numSubsets() const = 0;
};

//-----------------------------------------------------------------------
// Forward declaration
class Set;

//-----------------------------------------------------------------------
//! Subsets - controls how lattices are looped
class Subset 
{
public:
  //! There can be an empty constructor
  Subset();

  //! Copy constructor
  Subset(const Subset& s);


  // Simple constructor
  void make(const Subset& s);

  int getIdSiteTable() const {
    return *idSiteTable;
  }

  int getIdMemberTable() const {
    return *idMemberTable;
  }

  //! The = operator
  Subset& operator=(const Subset& s);

  //! Access the coloring for this subset
  int color() const {return sub_index;}

  multi1d<bool>& getIsElement() const       { return *membertable; }
  bool           isElement(int index) const { return (*membertable)[index]; }

  void setId(int _id) { id = _id; }
  int getId() const { return id; }


protected:
  // Simple constructor
  void make(bool rep, int start, int end, multi1d<int>* ind, int* ind_id, int cb, Set* set, multi1d<bool>* memb, int* memb_id , int id );

private:
  bool ordRep;
  int startSite;
  int endSite;
  int sub_index;

  //! Site lookup table
  multi1d<int>* sitetable;
  int* idSiteTable;

  //! Original set
  Set *set;

  // Constant time to know whether linear index in this subset
  multi1d<bool>* membertable;
  int* idMemberTable;

  int id; // masterset
  
public:
  inline bool hasOrderedRep() const {return ordRep;}
  inline int start() const {return startSite;}
  inline int end() const {return endSite;}

  const multi1d<int>& siteTable() const {return *sitetable;}
  inline int numSiteTable() const {return sitetable->size();}

  //! The super-set of this subset
  const Set& getSet() const { return *set; }

  friend class Set;
};


//-----------------------------------------------------------------------
//! Set - collection of subsets controlling which sites are involved in an operation
class Set 
{
public:
  //! There can be an empty constructor
  Set();

  //! Constructor from a function object
  Set(const SetFunc& fn);

  //! Constructor from a function object
  void make(const SetFunc& fn);

  //! Index operator selects a subset from a set
  const Subset& operator[](int subset_index) const {return sub[subset_index];}
        Subset& operator[](int subset_index)       {return sub[subset_index];}

  //! Return number of subsets
  int numSubsets() const {return sub.size();}

  //! Destructor for a set
  ~Set();

  //! The = operator
  Set& operator=(const Set& s);

  void signOffTables();


protected:
  //! A set is composed of an array of subsets
  multi1d<Subset> sub;

  //! Index or color array of lattice
  multi1d<int> lat_color;

  //! Array of sitetable arrays
  multi1d<multi1d<int> > sitetables;

  //! Array of sitetable arrays
  multi1d<multi1d<bool> > membertables;

  multi1d<int> idSiteTable;
  multi1d<int> idMemberTable;
  
  // Cache registered
  bool registered;


public:
  //! The coloring of the lattice sites
  const multi1d<int>& latticeColoring() const {return lat_color;}
};



//-----------------------------------------------------------------------
//! Default all subset
extern Subset all;


//! Experimental 3d checkerboarding for temp_precond
extern Set rb3;

//! Default 2-checkerboard (red/black) subset
extern Set rb;

//! Default 2^{Nd+1}-checkerboard subset. Useful for pure gauge updating.
extern Set mcb;

//! Default even subset
extern Subset even;

//! Default odd subset
extern Subset odd;


/** @} */ // end of group subsetss

} // namespace QDP

#endif
