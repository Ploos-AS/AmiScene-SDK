import sys
import unittest
from amiscene.blit import descriptor,parse,bltcon0,bltcon1,bltsize,emit_asm

class BlitTests(unittest.TestCase):
 def test_copy_a_descriptor(self):
  d=descriptor(channels="ad",minterm=0xf0,width=20,height=256)
  self.assertEqual(bltcon0(d),0x09f0);self.assertEqual(bltsize(d),0x4014)
 def test_cookie_cut_channels_and_minterm(self):
  self.assertEqual(bltcon0(descriptor(channels="abcd",minterm=0xca)),0x0fca)
 def test_masks_shifts_modulos_emit_readably(self):
  out=emit_asm(descriptor(ashift=3,bshift=7,afwm=0xff00,alwm=0x00ff,amod=-2,dmod=40),"Bob")
  self.assertIn("$39f0",out);self.assertIn("$7000",out);self.assertIn("$fffe",out);self.assertIn("$0028",out)
 def test_rejects_invalid_dimensions(self):
  with self.assertRaises(ValueError):descriptor(width=65)
  with self.assertRaises(ValueError):descriptor(height=0)
 def test_reference_copy_source(self):
  from pathlib import Path
  d=parse(Path("examples/blit/copy.blit").read_text())
  self.assertEqual(bltcon0(d),0x09f0);self.assertEqual(bltcon1(d),0);self.assertEqual(bltsize(d),0x0414)
 def test_reference_cookie_cut_source(self):
  from pathlib import Path
  d=parse(Path("examples/blit/cookie-cut.blit").read_text())
  self.assertEqual(bltcon0(d),0x0fca);self.assertEqual(bltsize(d),0x0402)
 def test_cli_named_minterm(self):
  from amiscene.cli import main
  import tempfile
  from pathlib import Path
  with tempfile.TemporaryDirectory() as td:
   out=Path(td)/"blit.s";old=sys.argv
   try:
    sys.argv=["amiscene","blit","--width","20","--height","16","--minterm","copy_a","--channels","ad","--label","Copy","-o",str(out)]
    self.assertEqual(main(),0)
   finally:sys.argv=old
   text=out.read_text();self.assertIn("Copy:",text);self.assertIn("$09f0",text)

if __name__=="__main__":unittest.main()
