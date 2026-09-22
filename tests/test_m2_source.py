import unittest
from host.amiscene.copper import parse,validate,emit_asm,register
class CopperSourceTests(unittest.TestCase):
 def test_parse(self):
  c=parse("WAIT 44,0\nMOVE COLOR00,$00f\nEND\n");self.assertEqual(c[1],("move",("COLOR00",15)));self.assertEqual(validate(c),[])
 def test_register_map(self):self.assertEqual(register("BPL1PTH"),0x0e0);self.assertEqual(register("SPR7CTL"),0x17a);self.assertEqual(register("COLOR31"),0x1be)
 def test_missing_end(self):self.assertIn("END",validate(parse("MOVE COLOR00,$000")))
 def test_backwards_wait(self):self.assertTrue(validate(parse("WAIT 100,0\nWAIT 50,0\nEND")))
 def test_source_to_asm(self):self.assertIn("$0180,$000f",emit_asm(parse("WAIT 44 0\nMOVE COLOR00 $00f\nEND"),"Copper"))
if __name__=="__main__":unittest.main()
