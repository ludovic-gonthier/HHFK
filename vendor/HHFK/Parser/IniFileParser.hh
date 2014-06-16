<?hh //strict
namespace HHFK\Parser;

use HHFK\Exception\FileFormatException;

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
	 * @throws FileFormatException If parse_ini_file fails
	 */
	public function parseFile(string $filename): array
	{
		$ini = \parse_ini_file($filename, true);
		if ($ini === false){
			throw new FileFormatException("INI file: '" . $filename . "'. Not correctly formatted INI file");
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