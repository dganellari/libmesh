// $Id: face_quad8.h,v 1.4 2004-11-15 22:09:12 benkirk Exp $

// The libMesh Finite Element Library.
// Copyright (C) 2002-2004  Benjamin S. Kirk, John W. Peterson
  
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
  
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
  
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA



#ifndef __quad8_h__
#define __quad8_h__


// C++ includes


// Local includes
#include "libmesh_common.h"
#include "face_quad.h"



// Forward declarations
class Mesh;



/**
 * The \p QUAD8 is an element in 2D composed of 8 nodes.
 * It is numbered like this:
 * \verbatim
 *        3     6     2
 * QUAD8: o-----o-----o
 *        |           |
 *        |           |
 *      7 o           o 5
 *        |           |
 *        |           |
 *        o-----o-----o
 *        0     4     1
 * \endverbatim
 */

// ------------------------------------------------------------
// Quad8 class definition
class Quad8 : public Quad
{
public:

  /**
   * Constructor. By default this element has no parent.
   */
  Quad8 (const Elem* p=NULL) :
    Quad(Quad8::n_nodes(), p) {}
 
  /**
   * Constructor.  Explicitly specifies the number of
   * nodes and neighbors for which storage will be allocated.
   */
  Quad8 (const unsigned int nn,
	 const unsigned int ns,
	 const Elem* p) :
    Quad(nn, ns, p) {}
  
  /**
   * @returns \p QUAD8
   */
  ElemType type () const { return QUAD8; }

  /**
   * @returns 8
   */
  unsigned int n_nodes() const { return 8; }
  
  /**
   * @returns 4
   */
  unsigned int n_sides() const { return 4; }
  
  /**
   * @returns 4
   */
  unsigned int n_children() const { return 4; }
  
  /**
   * @returns 5
   */
  unsigned int n_sub_elem() const { return 5; }
  
  /**
   * @returns SECOND
   */
  Order default_order() const { return SECOND; }

  /**
   * @returns an id associated with the \p s side of this element.
   * The id is not necessariy unique, but should be close.  This is
   * particularly useful in the \p MeshBase::find_neighbors() routine.
   *
   * We reimplemenet this method here for the \p Quad8 since we can
   * use the center node of each edge to provide a perfect (unique)
   * key.
   */
  unsigned int key (const unsigned int s) const;
  
  AutoPtr<Elem> build_side (const unsigned int i) const;

  virtual void connectivity(const unsigned int sf,
			    const IOPackage iop,
			    std::vector<unsigned int>& conn) const;

//   void tecplot_connectivity(const unsigned int sf,
// 			    std::vector<unsigned int>& conn) const;
  
  
//   void vtk_connectivity(const unsigned int sc,
// 			std::vector<unsigned int> *conn = NULL) const;

//   unsigned int vtk_element_type (const unsigned int sc) const;

  /**
   * @returns 2 for all \p n
   */
  unsigned int n_second_order_adjacent_vertices (const unsigned int) const
      { return 2; }

  /**
   * @returns the element-local number of the  \f$ v^{th} \f$ vertex
   * that defines the \f$ n^{th} \f$ second-order node.
   * Note that \p n is counted as depicted above, \f$ 4 \le n < 8 \f$.
   */
  unsigned short int second_order_adjacent_vertex (const unsigned int n,
						   const unsigned int v) const;
  
  
protected:
  
  
#ifdef ENABLE_AMR
  
  /**
   * Matrix used to create the elements children.
   */
  float embedding_matrix (const unsigned int i,
			  const unsigned int j,
			  const unsigned int k) const
  { return _embedding_matrix[i][j][k]; }

  /**
   * Matrix that computes new nodal locations/solution values
   * from current nodes/solution.
   */
  static const float _embedding_matrix[4][8][8];
  
#endif
 
};

// ------------------------------------------------------------
// Quad8 class member functions


#endif
