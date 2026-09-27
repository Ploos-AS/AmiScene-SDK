import sys
import unittest
from amiscene.blit import descriptor,fill_descriptor,line_descriptor,parse,bltcon0,bltcon1,bltsize,emit_asm

class BlitTests(unittest.TestCase):
 def test_copy_a_descriptor(self):
  d=descriptor(channels="ad",minterm=0xf0,width=20,height=256)
  self.assertEqual(bltcon0(d),0x09f0);self.assertEqual(bltsize(d),0x4014)
 def test_cookie_cut_channels_and_minterm(self):
  self.assertEqual(bltcon0(descriptor(channels="abcd",minterm=0xca)),0x0fca)
 def test_masks_shifts_modulos_emit_readably(self):
  out=emit_asm(descriptor(ashift=3,bshift=7,afwm=0xff00,alwm=0x00ff,amod=-2,dmod=40),"Bob")
  self.assertIn("$39f0",out);self.assertIn("$7000",out);self.assertIn("$fffe",out);self.assertIn("$0028",out)
 def test_line_horizontal_registers(self):
  d=line_descriptor(0,0,15,0,40)
  self.assertEqual(d["bltcon0"],0x0b4a);self.assertEqual(d["bltcon1"],0x0059)
  self.assertEqual(d["apt"],-30);self.assertEqual(d["amod"],-60);self.assertEqual(d["bmod"],0)
  self.assertEqual(d["cmod"],40);self.assertEqual(d["dmod"],40);self.assertEqual(d["width"],2);self.assertEqual(d["height"],16)
 def test_line_texture_and_one_dot(self):
  d=line_descriptor(3,2,3,9,40,texture=0xaaaa,texture_start=5,one_dot=True)
  self.assertEqual(d["bdat"],0xaaaa);self.assertEqual(d["bltcon1"]>>12,5);self.assertTrue(d["bltcon1"]&2)
 def test_line_rejects_over_1024(self):
  with self.assertRaises(ValueError):line_descriptor(0,0,1024,0,40)
 def test_inclusive_fill_is_descending(self):
  d=fill_descriptor("inclusive")
  self.assertEqual(bltcon1(d),0x000a)
 def test_exclusive_fill_with_carry(self):
  d=fill_descriptor("exclusive",carry=True)
  self.assertEqual(bltcon1(d),0x0016)
 def test_rejects_both_fill_modes(self):
  with self.assertRaises(ValueError):fill_descriptor("both")
 def test_rejects_invalid_dimensions(self):
  with self.assertRaises(ValueError):descriptor(width=65)
  with self.assertRaises(ValueError):descriptor(height=0)
 def test_reference_copy_source(self):
  from pathlib import Path
  d=parse(Path("examples/blit/copy.blit").read_text())
  self.assertEqual(bltcon0(d),0x09f0);self.assertEqual(bltcon1(d),0);self.assertEqual(bltsize(d),0x0414)
 def test_reference_fill_source(self):
  from pathlib import Path
  d=parse(Path("examples/blit/fill-inclusive.blit").read_text())
  self.assertEqual(bltcon0(d),0x09f0);self.assertEqual(bltcon1(d),0x000a);self.assertEqual(bltsize(d),0x0402)
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
