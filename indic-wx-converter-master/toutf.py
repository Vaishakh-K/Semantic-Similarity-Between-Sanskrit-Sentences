#!/usr/bin/env python
from converter_indic import wxConvert
con = wxConvert(order='wx2utf', lang='hin')
hin = """rAmaH akRay"""
print con.convert(hin)
