from pathlib import Path

script_dir_path = Path(__file__).parent.absolute()
with open(script_dir_path / "settings.bin", "wb") as settings_file:
	settings_file.write(b'\x00')
