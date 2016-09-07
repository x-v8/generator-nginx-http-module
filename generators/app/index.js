'use strict';
var yeoman = require('yeoman-generator');
var chalk = require('chalk');
var yosay = require('yosay');

var ctx_hooks = [
  'preconfiguration',
  'postconfiguration',
  'create_main_configuration',
  'init_main_configuration',
  'create_server_configuration',
  'merge_server_configuration',
  'create_location_configuration',
  'merge_location_configuration',
];

module.exports = yeoman.Base.extend({
  prompting: function () {
    // Have Yeoman greet the user.
    this.log(yosay(
      'Welcome to the stupendous ' + chalk.red('generator-nginx-http-module') + ' generator!'
    ));

    var prompts = [
      {
        type: 'input',
        name: 'name',
        message: 'what\'s your module name',
      },
      {
        type: 'list',
        name: 'phase',
        message: 'which phase is your module working on',
        choices: ['NGX_HTTP_POST_READ_PHASE',
                  'NGX_HTTP_SERVER_REWRITE_PHASE',
                  'NGX_HTTP_REWRITE_PHASE',
                  'NGX_HTTP_PREACCESS_PHASE',
                  'NGX_HTTP_ACCESS_PHASE',
                  'NGX_HTTP_CONTENT_PHASE',
                  'NGX_HTTP_LOG_PHASE'],
        default: 'NGX_HTTP_CONTENT_PHASE',
      },
      {
        type: 'checkbox',
        name: 'ctx',
        message: 'which hook do you need on module ctx',
        choices: ctx_hooks,
        default: 'create_location_configuration'
      }
    ];

    return this.prompt(prompts).then(function (props) {
      // To access props later use this.props.someAnswer;

      var ctx = {};
      for (var i = 0; i < ctx_hooks.length; i++) {
        var hook = ctx_hooks[i];
        if (props.ctx.indexOf(hook) !== -1) {
          ctx[hook] = true;
        }
      }
      props.ctx = ctx;
      this.props = props;
    }.bind(this));
  },

  writing: function () {
    this.fs.copy(
      this.templatePath('ddebug.h'),
      this.destinationPath(`src/ddebug.h`)
    );
    this.fs.copyTpl(
      this.templatePath('ngx_http_module.c'),
      this.destinationPath(`src/${this.props.name}.c`),
      {
        name: this.props.name,
        phase: this.props.phase,
        ctx: this.props.ctx
      }
    );
    this.fs.copyTpl(
      this.templatePath('ngx_http_module.h'),
      this.destinationPath(`src/${this.props.name}.h`),
      {
        name: this.props.name,
        phase: this.props.phase,
        ctx: this.props.ctx
      }
    );
  },

  install: function () {
  }
});