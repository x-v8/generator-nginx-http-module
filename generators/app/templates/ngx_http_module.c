#ifndef DDEBUG
#define DDEBUG 0
#endif
#include "ddebug.h"

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

#include "<%= name %>.h"

<% if (ctx.preconfiguration) { -%>
static ngx_int_t
<%= name %>_pre_conf(ngx_conf_t *cf);
<% } -%>
<% if (ctx.postconfiguration) { -%>
static ngx_int_t
<%= name %>_post_conf(ngx_conf_t *cf);
<% } -%>
<% if (ctx.create_main_configuration) { -%>
static void *
<%= name %>_create_main_conf(ngx_conf_t *cf);
<% } -%>
<% if (ctx.init_main_configuration) { -%>
static char *
<%= name %>_init_main_conf(ngx_conf_t *cf, void *conf);
<% } -%>
<% if (ctx.create_server_configuration) { -%>
static void *
<%= name %>_create_server_conf(ngx_conf_t *cf);
<% } -%>
<% if (ctx.merge_server_configuration) { -%>
static char *
<%= name %>_merge_server_conf(ngx_conf_t *cf, void *prev, void *conf);
<% } -%>
<% if (ctx.create_location_configuration) { -%>
static void *
<%= name %>_create_loc_conf(ngx_conf_t *cf);
<% } -%>
<% if (ctx.mrege_location_configuration) { -%>
static char *
<%= name %>_merge_loc_conf(ngx_conf_t *cf, void *prev, void *conf);
<% } -%>

static ngx_http_module_t  <%= name %>_ctx = {
    <% if (ctx.preconfiguration) { -%>
        <%= name %>_pre_conf,
    <% } else { -%>
        NULL,
    <% } -%>
    <% if (ctx.postconfiguration) { -%>
        <%= name %>_post_conf,
    <% } else { -%>
        NULL,
    <% } -%>

    <% if (ctx.create_main_configuration) { -%>
        <%= name %>_create_main_conf,
    <% } else { -%>
        NULL,
    <% } -%>
    <% if (ctx.init_main_configuration) { -%>
        <%= name %>_init_main_conf,
    <% } else { -%>
        NULL,
    <% } -%>

    <% if (ctx.create_server_configuration) { -%>
        <%= name %>_create_server_conf,
    <% } else { -%>
        NULL,
    <% } -%>
    <% if (ctx.merge_server_configuration) { -%>
        <%= name %>_merge_server_conf,
    <% } else { -%>
        NULL,
    <% } -%>

    <% if (ctx.create_location_configuration) { -%>
        <%= name %>_create_loc_conf,
    <% } else { -%>
        NULL,
    <% } -%>
    <% if (ctx.mrege_location_configuration) { -%>
        <%= name %>_merge_loc_conf,
    <% } else { -%>
        NULL,
    <% } -%>
};


ngx_module_t <%= name %> = {
    NGX_MODULE_V1,
    &<%= name %>_ctx,                      /* module context */
    <%= name %>_commands,                  /* module directives */
    NGX_HTTP_MODULE,                       /* module type */
    NULL,                                  /* init master */
    NULL,                                  /* init module */
    NULL,                                  /* init process */
    NULL,                                  /* init thread */
    NULL,                                  /* exit thread */
    NULL,                                  /* exit process */
    NULL,                                  /* exit master */
    NGX_MODULE_V1_PADDING
};