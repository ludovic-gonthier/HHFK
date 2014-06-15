<?hh //strict
namespace HHFK\Parser;

class IniFileParser
{
	/**
	 * Parse an INI file, creating subsection
	 * e.g
	 * [section] 
	 * [section:sub-section]
	 *    data=value
	 * 
	 * @param  string $filename
	 * @return The array containing the configuration lodaded from the file
	 */
	public function parseFile(string $filename): array
	{
		$ini = \parse_ini_file($filename, true);
		if ($ini === false){
			## TODO Correct Exception
			throw new \Exception("INI file not correctly formatted");
		}

		$configuration = array();
		foreach ($ini as $key => $value) {
			$split = explode(":", $key);
			if (count($split) === 1) {
				$configuration[trim($key)] = $value;
				continue;
			}

			$array_ref = &$configuration;
			foreach ($split as $section) {
				$section = trim($section);
				if (empty($array_ref[$section])) {
					$array_ref[$section] = array();
				}
				$array_ref = &$array_ref[$section];
			}
			$array_ref = $value;
		}
		return $configuration;
	}
}