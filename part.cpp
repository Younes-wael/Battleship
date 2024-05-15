#include "part.h"
#include <iostream>

using namespace std;

    /**
   * @brief Part constructor
   * @param[in] row The grid row on which this part is to be placed
   * @param[in] col The grid column on which this part is to be placed
   *
   * This is supposed to be the only Part constructor. The values for \ref m_row
   * and \ref m_col shall be assigned from `row` and `col` respectively.
   * The status \ref m_status shall be initialized with 0. indicating 'no
   * damage'.
   */
  part::part(int row, int col): m_row(row),m_col(col), m_status(0){}

    /**
   * @brief Returns wether or not this part is damaged
   * @return True if damaged, False if undamaged
   *
   * Note that there is no extra status for a sunken \ref Ship.
   * By definition, a ship is sunk when all parts were hit, e.g. are damaged.
   */
    bool part::isDamaged() const{

        return (m_status != 0);
    }

    /**
   * @brief Sets the status of this part to a valued representing 'damaged'.
   *
   * The attribute \ref m_status is supposed to be 0 if there is no damage,
   * and 1 if this part was damaged.
   * This method shall thereby set \ref m_status to 1.
   */
    void part::setDamaged(){
        m_status=1;
    }

    /**
   * @brief Returns the row with which this part was constructed
   * @return The row with which this part was constructed
   */
    int part::getRow() const{
        return m_row;
    }

    /**
   * @brief Returns the column with which this part was constructed
   * @return The column with which this part was constructed
   */
    int part::getCol() const{
        return m_col;
    }

