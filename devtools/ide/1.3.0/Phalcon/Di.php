<?php 

namespace Phalcon {

	/**
	 * Phalcon\Di
	 *
	 * Phalcon\Di is a component that implements Dependency Injection/Service Location
	 * of services and it's itself a container for them.
	 *
	 * Since Phalcon is highly decoupled, Phalcon\Di is essential to integrate the different
	 * components of the framework. The developer can also use this component to inject dependencies
	 * and manage global instances of the different classes used in the application.
	 *
	 * Basically, this component implements the `Inversion of Control` pattern. Applying this,
	 * the objects do not receive their dependencies using setters or constructors, but requesting
	 * a service dependency injector. This reduces the overall complexity, since there is only one
	 * way to get the required dependencies within a component.
	 *
	 * Additionally, this pattern increases testability in the code, thus making it less prone to errors.
	 *
	 *<code>
	 * $di = new Phalcon\Di();
	 *
	 * //Using a string definition
	 * $di->set('request', 'Phalcon\Http\Request', true);
	 *
	 * //Using an anonymous function
	 * $di->set('request', function(){
	 *	  return new Phalcon\Http\Request();
	 * }, true);
	 *
	 * $request = $di->getRequest();
	 *
	 *</code>
	 */
	
	class Di implements \Phalcon\DiInterface {

		protected $_name;

		protected $_services;

		protected $_sharedInstances;

		protected $_freshInstance;

		protected static $_default;

		protected static $_list;

		protected $_eventsManager;

		/**
		 * \Phalcon\Di constructor
		 *
		 */
		public function __construct($name=null){ }


		/**
		 * Returns the name
		 *
		 * @return String
		 */
		public function getName(){ }


		/**
		 * Sets a custom events manager
		 *
		 * @param \Phalcon\Events\ManagerInterface $eventsManager
		 */
		protected function setEventsManager(){ }


		/**
		 * Returns the custom events manager
		 *
		 * @return \Phalcon\Events\ManagerInterface
		 */
		protected function getEventsManager(){ }


		/**
		 * Registers a service in the services container
		 *
		 * @param string $name
		 * @param mixed $definition
		 * @param boolean $shared
		 * @return \Phalcon\Di\ServiceInterface
		 */
		public function set($name, $definition, $shared=null){ }


		/**
		 * Removes a service in the services container
		 *
		 * @param string $name
		 */
		public function remove($name){ }


		/**
		 * Returns a service definition without resolving
		 *
		 * @param string $name
		 * @param mixed $definition
		 * @param boolean $shared
		 * @return \Phalcon\Di\ServiceInterface
		 */
		public function setRaw($name, $definition=null, $shared=null){ }


		/**
		 * Returns a service definition without resolving
		 *
		 * @param string $name
		 * @return mixed
		 */
		public function getRaw($name){ }


		/**
		 * Returns a \Phalcon\Di\Service instance
		 *
		 * @param string $name
		 * @return \Phalcon\Di\ServiceInterface
		 */
		public function getService($name){ }


		/**
		 * Sets a service using a raw \Phalcon\Di\Service definition
		 *
		 * @param string $name
		 * @param \Phalcon\Di\ServiceInterface $service
		 * @return \Phalcon\Di\ServiceInterface
		 */
		public function setService($name, \Phalcon\Di\ServiceInterface $rawDefinition){ }


		/**
		 * Resolves the service based on its configuration
		 *
		 * @param string $name
		 * @param array $parameters
		 * @param boolean $noError
		 * @return mixed
		 */
		public function get($name, $parameters=null, $noError=null, $noerror=null){ }


		/**
		 * Resolves a service, the resolved service is stored in the DI, subsequent requests for this service will return the same instance
		 *
		 * @param string $name
		 * @param array $parameters
		 * @param boolean $noError
		 * @return mixed
		 */
		public function getShared($name, $parameters=null, $noError=null){ }


		/**
		 * Check whether the DI contains a service by a name
		 *
		 * @param string $name
		 * @return boolean
		 */
		public function has($name){ }


		/**
		 * Check whether the last service obtained via getShared produced a fresh instance or an existing one
		 *
		 * @return boolean
		 */
		public function wasFreshInstance(){ }


		/**
		 * Return the services registered in the DI
		 *
		 * @return \Phalcon\Di\Service[]
		 */
		public function getServices(){ }


		/**
		 * Set a default dependency injection container to be obtained into static methods
		 *
		 * @param \Phalcon\DiInterface $dependencyInjector
		 */
		public static function setDefault(\Phalcon\DiInterface $dependencyInjector){ }


		/**
		 * Return the lastest DI created
		 *
		 * @return \Phalcon\DiInterface
		 */
		public static function getDefault(){ }


		/**
		 * Resets the internal default DI
		 */
		public static function reset(){ }


		/**
		 * Attempts to register a service in the services container
		 * Only is successful if a service hasn't been registered previously
		 * with the same name
		 *
		 * @param string $name
		 * @param mixed $definition
		 * @param boolean $shared
		 * @return \Phalcon\Di\ServiceInterface
		 */
		public function attempt($name, $definition, $shared=null){ }


		/**
		 * Registers an "always shared" service in the services container
		 *
		 * @param string $name
		 * @param mixed $definition
		 * @return \Phalcon\Di\ServiceInterface
		 */
		public function setShared($name, $definition){ }


		/**
		 * Check if a service is registered using the array syntax.
		 * Alias for \Phalcon\Di::has()
		 *
		 * @param string $name
		 * @return boolean
		 */
		public function offsetExists($property){ }


		/**
		 * Allows to register a shared service using the array syntax.
		 * Alias for \Phalcon\Di::setShared()
		 *
		 *<code>
		 *	$di['request'] = new \Phalcon\Http\Request();
		 *</code>
		 *
		 * @param string $name
		 * @param mixed $definition
		 */
		public function offsetSet($property, $value){ }


		/**
		 * Allows to obtain a shared service using the array syntax.
		 * Alias for \Phalcon\Di::getShared()
		 *
		 *<code>
		 *	var_dump($di['request']);
		 *</code>
		 *
		 * @param string $name
		 * @return mixed
		 */
		public function offsetGet($property){ }


		/**
		 * Removes a service from the services container using the array syntax.
		 * Alias for \Phalcon\Di::remove()
		 *
		 * @param string $name
		 */
		public function offsetUnset($property){ }


		/**
		 * Magic method to get or set services using setters/getters
		 *
		 * @param string $method
		 * @param array $arguments
		 * @return mixed
		 */
		public function __call($method, $arguments=null){ }


		public function __clone(){ }


		public function __set($property, $value){ }


		public function __get($property){ }

	}
}
