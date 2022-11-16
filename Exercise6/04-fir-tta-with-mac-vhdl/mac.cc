/**
 * OSAL behavior definition file for Multiply-Accumulate.
 */

#include "OSAL.hh"

DEFINE_STATE(ACCUMULATOR)
  SIntWord value;

  INIT_STATE(ACCUMULATOR)
    value = 0;
  END_INIT_STATE;

END_DEFINE_STATE;

OPERATION_WITH_STATE(MAC32, ACCUMULATOR)
  TRIGGER

  int a = INT(1);
  int b = INT(2);
  int c = STATE.value;

  c = c + (a*b);
  STATE.value = c;
  IO(3) = c;

  return true;

  END_TRIGGER;
END_OPERATION_WITH_STATE(MAC32)

OPERATION_WITH_STATE(SET_ACC, ACCUMULATOR)
  TRIGGER

  STATE.value = INT(1);

  return true;

  END_TRIGGER;
END_OPERATION_WITH_STATE(SET_ACC)
