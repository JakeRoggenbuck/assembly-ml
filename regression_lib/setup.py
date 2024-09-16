from distutils.core import setup, Extension

def main():
    setup(name="regression_lib",
          version="1.0.0",
          description="Python interface for C linear regression",
          author="<your name>",
          author_email="your_email@gmail.com",
          ext_modules=[Extension("regression_lib", ["main.c"])])

if __name__ == "__main__":
    main()
