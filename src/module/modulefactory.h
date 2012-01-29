template <typename base>
class ModuleFactory
    {
        public:

        template <typename derived>
             void reg(std::string const& name)
             {
                 modules[name] = "?????";
             }
        typedef std::map<std::string, base_type> modules_container;

        modules_container modules;
     };
