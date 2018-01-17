#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os, sys
from converter_indic import wxConvert
con = wxConvert(order='utf2wx')  # here default language is hindi and default format is text
hin = """देश भर में अब तक हुई बारिश औसत से छह फीसदी कम है जबकि विभाग का दावा था कि इसमें ५ फीसदी से ज्यादा कमी नहीं होगी"""
print con.convert(hin)
