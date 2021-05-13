#ifndef QDP_MAPRESOURCE
#define QDP_MAPRESOURCE




namespace QDP {



  // A 2D container of resource classes.
  // We index msg_size and dest_node and take the
  // index as the coordinate in the 2D matrix.

class FnMapRsrcMatrix {

  multi2d< std::pair< int , std::vector<FnMapRsrc*> >* > m2d;
  std::vector<int> sendMsgSize;
  std::vector<int> destNode;
  unsigned int numSendMsgSize;
  unsigned int numDestNode;

  FnMapRsrcMatrix(): sendMsgSize(0),
		             destNode(0),
		             numSendMsgSize(32),
		             numDestNode(Nd*2) {
    m2d.resize(numSendMsgSize,numDestNode);

    for(unsigned int i=0;i<numSendMsgSize;i++) {
      for(unsigned int q=0;q<numDestNode;q++) {
	m2d(i,q)=new std::pair< int , std::vector<FnMapRsrc*> >;
	(*m2d(i,q)).first=0;
      }
    }
  }


  public:

  void cleanup();
#if 0
  {
    //QDPIO::cout << "FnMapRsrcMatrix cleanup\n";
    for(unsigned int i=0;i<numSendMsgSize;i++) {
      for(unsigned int q=0;q<numDestNode;q++) {
	//QDPIO::cout << "cleanup m2d(" << i << "," << q << ")\n";
	for (std::vector<FnMapRsrc*>::iterator v = (*m2d(i,q)).second.begin() ; v != (*m2d(i,q)).second.end() ; ++v )
	  delete *v;
	//std::for_each( (*m2d(i,q)).second.begin() , (*m2d(i,q)).second.end() , this->*del );
	delete m2d(i,q);
      }
    }
  }
#endif

  std::pair< int , std::vector<FnMapRsrc*> >* get(int _destNode,int _srcNode,
						  int _sendMsgSize,int _rcvMsgSize);
#if 0
  {
    bool found = false;
    unsigned int xDestNode=0;
    for(; xDestNode < destNode.size(); ++xDestNode)
      if (destNode[xDestNode] == _destNode)
	{
	  found = true;
	  break;
	}
    if (! found) {
      if (destNode.size() == numDestNode) {
	QDP_error_exit("FnMapRsrcMatrix not enough space in destNode");
      } else {
	destNode.push_back(_destNode);
	xDestNode=destNode.size()-1;
      }
    }
    //QDPIO::cout << "using node place = " << xDestNode << "\n";


    found = false;
    unsigned int xSendmsgsize=0;
    for(; xSendmsgsize < sendMsgSize.size(); ++xSendmsgsize)
      if (sendMsgSize[xSendmsgsize] == _sendMsgSize)
	{
	  found = true;
	  break;
	}
    if (! found) {
      if (sendMsgSize.size() == numSendMsgSize) {
	QDP_error_exit("FnMapRsrcMatrix not enough space in sendmsgsize");
      } else {
	sendMsgSize.push_back(_sendMsgSize);
	xSendmsgsize=sendMsgSize.size()-1;
      }
    }
    //QDPIO::cout << "using msg_size place = " << xSendmsgsize << "\n";

    std::pair< int , std::vector<FnMapRsrc*> >& pos = *m2d(xSendmsgsize,xDestNode);

#if QDP_DEBUG >= 3
    // SANITY
    if ( pos.second.size() <  pos.first )
      QDP_error_exit(" pos.second.size()=%d  pos.first=%d",pos.second.size(), pos.first);
#endif

    // Vector's size large enough ?
    if ( pos.second.size() ==  (unsigned)pos.first ) {
      //QDPIO::cout << "allocate and setup new rsrc-obj (destnode=" << _destNode << ",sndmsgsize=" << _sendMsgSize << ")\n";
      pos.second.push_back( new FnMapRsrc() );
      pos.second.at(pos.first)->setup( _destNode, _srcNode, _sendMsgSize, _rcvMsgSize );
    }

    //QDPIO::cout << "returning rsrc-obj " << pos.first << "\n";

    return &pos;
  }
#endif
  
  static FnMapRsrcMatrix& Instance() {
    static FnMapRsrcMatrix singleton;
    return singleton;
  }

};


  // This wrapper is used, since FnMap's are copy-constructed
  // during recursing down the expression with forEach. Thus a
  // shared_ptr to this wrapper ensures that the original and copy
  // point to the same resource class.

class RsrcWrapper
{
  const multi1d<int>& destnodes;
  const multi1d<int>& srcenodes;
  std::pair< int , std::vector<FnMapRsrc*> > * pPair;
  const FnMapRsrc* cached;
  bool rAlloc;
public:
  ~RsrcWrapper() {
    if (rAlloc) {
      pPair->first--;
      //QDPIO::cout << "wrapper destructor: counting down to " << pPair->first << "\n";
#if QDP_DEBUG >= 3
      if (pPair->first < 0)
	QDP_error_exit("<0");
#endif
    }
  }
  RsrcWrapper(  const multi1d<int>& destnodes_, const multi1d<int>& srcenodes_): 
    destnodes(destnodes_),srcenodes(srcenodes_),cached(NULL),rAlloc(false) {
  }

  const FnMapRsrc& getResource(int srcnum_, int dstnum_) {
#if QDP_DEBUG >= 3
    if ( !srcenodes.size() || !destnodes.size() )
      QDP_error_exit("FnMapRsrc& getResource srcnode_size=%d destnode_size=%d", srcenodes.size() , destnodes.size() );
#endif
    pPair = FnMapRsrcMatrix::Instance().get( destnodes[0] , srcenodes[0] , dstnum_ , srcnum_ );
    cached = pPair->second.at(pPair->first++);
    rAlloc=true;
    return *cached;
  }

  const FnMapRsrc& get() const {
#if QDP_DEBUG >= 3
    if (!rAlloc)
      QDP_error_exit("RsrcWrapper::get() internal error");
#endif
    assert(cached);
    return *cached;
  }

};








} // namespace QDP

#endif
