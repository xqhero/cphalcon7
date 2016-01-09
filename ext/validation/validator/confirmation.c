
/*
  +------------------------------------------------------------------------+
  | Phalcon Framework                                                      |
  +------------------------------------------------------------------------+
  | Copyright (c) 2011-2014 Phalcon Team (http://www.phalconphp.com)       |
  +------------------------------------------------------------------------+
  | This source file is subject to the New BSD License that is bundled     |
  | with this package in the file docs/LICENSE.txt.                        |
  |                                                                        |
  | If you did not receive a copy of the license and are unable to         |
  | obtain it through the world-wide-web, please send an email             |
  | to license@phalconphp.com so we can send you a copy immediately.       |
  +------------------------------------------------------------------------+
  | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
  |          Eduar Carvajal <eduar@phalconphp.com>                         |
  +------------------------------------------------------------------------+
*/

#include "validation/validator/confirmation.h"
#include "validation/validator.h"
#include "validation/validatorinterface.h"
#include "validation/message.h"
#include "validation/exception.h"
#include "validation.h"

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/concat.h"

#include "interned-strings.h"

/**
 * Phalcon\Validation\Validator\Confirmation
 *
 * Checks that two values have the same value
 *
 *<code>
 *use Phalcon\Validation\Validator\Confirmation;
 *
 *$validator->add('password', new Confirmation(array(
 *   'message' => 'Password doesn\'t match confirmation',
 *   'with' => 'confirmPassword'
 *)));
 *</code>
 */
zend_class_entry *phalcon_validation_validator_confirmation_ce;

PHP_METHOD(Phalcon_Validation_Validator_Confirmation, validate);
PHP_METHOD(Phalcon_Validation_Validator_Confirmation, valid);

static const zend_function_entry phalcon_validation_validator_confirmation_method_entry[] = {
	PHP_ME(Phalcon_Validation_Validator_Confirmation, validate, arginfo_phalcon_validation_validatorinterface_validate, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Validation_Validator_Confirmation, valid, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

/**
 * Phalcon\Validation\Validator\Confirmation initializer
 */
PHALCON_INIT_CLASS(Phalcon_Validation_Validator_Confirmation){

	PHALCON_REGISTER_CLASS_EX(Phalcon\\Validation\\Validator, Confirmation, validation_validator_confirmation, phalcon_validation_validator_ce, phalcon_validation_validator_confirmation_method_entry, 0);

	zend_class_implements(phalcon_validation_validator_confirmation_ce, 1, phalcon_validation_validatorinterface_ce);

	return SUCCESS;
}

/**
 * Executes the validation
 *
 * @param Phalcon\Validation $validator
 * @param string $attribute
 * @return boolean
 */
PHP_METHOD(Phalcon_Validation_Validator_Confirmation, validate){

	zval *validator, *attribute, with_attribute;
	zval *value = NULL, *with_value = NULL, *valid = NULL, message_str, *message, code;
	zval label, with_label, pairs, *prepared = NULL;
	zend_class_entry *ce = Z_OBJCE_P(getThis());

	PHALCON_MM_GROW();

	phalcon_fetch_params(1, 2, 0, &validator, &attribute);
	
	PHALCON_VERIFY_CLASS_EX(validator, phalcon_validation_ce, phalcon_validation_exception_ce, 1);

	RETURN_MM_ON_FAILURE(phalcon_validation_validator_getoption_helper(&with_attribute, ce, getThis(), "with"));
	
	PHALCON_CALL_METHOD(&value,      validator, "getvalue", attribute);
	PHALCON_CALL_METHOD(&with_value, validator, "getvalue", &with_attribute);

	PHALCON_CALL_SELF(&valid, "valid", value, with_value);
	
	if (PHALCON_IS_FALSE(valid)) {
		RETURN_MM_ON_FAILURE(phalcon_validation_validator_getoption_helper(&label, ce, getThis(), ISV(label)));
		if (!zend_is_true(&label)) {
			PHALCON_CALL_METHOD(&label, validator, "getlabel", attribute);
			if (!zend_is_true(&label)) {
				ZVAL_COPY_VALUE(&label, attribute);
			}
		}

		RETURN_MM_ON_FAILURE(phalcon_validation_validator_getoption_helper(&with_label, ce, getThis(), ISV(label)));
		if (!zend_is_true(&with_label)) {
			PHALCON_CALL_METHOD(&with_label, validator, "getlabel", &with_attribute);
			if (!zend_is_true(&with_label)) {
				ZVAL_COPY_VALUE(&with_label, &with_attribute);
			}
		}

		array_init_size(&pairs, 2);
		Z_TRY_ADDREF_P(&label);
		add_assoc_zval_ex(&pairs, SL(":field"), &label);
		Z_TRY_ADDREF_P(&with_label);
		add_assoc_zval_ex(&pairs, SL(":with"), &with_label);

		RETURN_MM_ON_FAILURE(phalcon_validation_validator_getoption_helper(&message_str, ce, getThis(), ISV(message)));
		if (!zend_is_true(&message_str)) {
			RETURN_MM_ON_FAILURE(phalcon_validation_getdefaultmessage_helper(&message_str, Z_OBJCE_P(validator), validator, "Confirmation"));
		}

		RETURN_MM_ON_FAILURE(phalcon_validation_validator_getoption_helper(&code, ce, getThis(), ISV(code)));
		if (Z_TYPE_P(&code) == IS_NULL) {
			ZVAL_LONG(&code, 0);
		}

		PHALCON_CALL_FUNCTION(&prepared, "strtr", &message_str, &pairs);
	
		message = phalcon_validation_message_construct_helper(prepared, attribute, "Confirmation", &code);
		Z_TRY_DELREF_P(message);
	
		PHALCON_CALL_METHOD(NULL, validator, "appendmessage", message);
		RETURN_MM_FALSE;
	}
	
	RETURN_MM_TRUE;
}

/**
 * Executes the validation
 *
 * @param string $value
 * @return boolean
 */
PHP_METHOD(Phalcon_Validation_Validator_Confirmation, valid){

	zval *value, *with_value;

	PHALCON_MM_GROW();

	phalcon_fetch_params(1, 2, 0, &value, &with_value);

	if (!PHALCON_IS_EQUAL(value, with_value)) {
		RETURN_MM_FALSE;
	}
	
	RETURN_MM_TRUE;
}
