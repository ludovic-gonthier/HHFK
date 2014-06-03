<?hh
namespace HHFK\AModule;

abstract class AModule
{
	public function getNamespace()
	{
		if (!isset($this->_namespace)){
			$reflect = new \ReflectionObject($this);
			$this->_namespace = $reflect->getNamespaceName();
		}
	}
	public function getPath()
	{
		if (!isset($this->_path)) {

		}
	}

	private string $_path;
	private string $_namespace;
}