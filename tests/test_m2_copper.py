import unittest
from host.amiscene.copper import register,move,wait,skip,end,emit_asm
class CopperTests(unittest.TestCase):
 def test_color_move(self):self.assertEqual(move("COLOR00",0x0f00),(0x180,0x0f00))
 def test_numeric_register(self):self.assertEqual(register(0x100),0x100)
 def test_bad_register(self):
  with self.assertRaises(ValueError):register(0x101)
 def test_wait(self):self.assertEqual(wait(100,40),(0x6429,0xfffe))
 def test_wait_bfd(self):self.assertEqual(wait(100,40,bfd=False),(0x6429,0x7ffe))
 def test_skip_bit(self):self.assertEqual(skip(100,40)[1]&1,1)
 def test_skip_bfd(self):self.assertEqual(skip(100,40)[1],0xffff)
 def test_end(self):self.assertEqual(end(),(0xffff,0xfffe))
 def test_asm(self):
  s=emit_asm([("wait",(44,0)),("move",("COLOR00",0x00f)),("end",())],"Copper");self.assertIn("WAIT",s);self.assertIn("MOVE COLOR00",s);self.assertIn("$ffff,$fffe",s)
if __name__=="__main__":unittest.main()
