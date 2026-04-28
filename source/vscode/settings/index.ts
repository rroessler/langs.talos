/// Vendor Modules
import * as vscode from 'vscode';

/// Talos Modules
import { Output } from '@/talos/output';
import { Product } from '@/talos/product';
import { Command } from '@/talos/command';
import { Extension } from '@/talos/extension';
import { Decorator, Disposable, Inversify } from '@/talos/utilities';

/** Available Settings Schema. */
export interface Settings {
    'server.executablePath': string;
    'server.loggingLevel': Output.Level;
}

export namespace Settings {
    //  TYPEDEFS  //

    @Inversify.injectable()
    @Decorator.Class.Rename('Settings.Service')
    class Service extends Disposable.Registry implements Extension.Contribution {
        //  INJECTABLES  //

        /** Commands Registry. */
        @Inversify.inject(Command.Registry) protected readonly m_commands!: Command.Registry;

        //  LIFECYCLE METHODS  //

        /** Handles configuring the service. */
        async configure() {
            this.m_subscribe(this.m_commands.register(Command.Key.SETTINGS, open));
        }
    }

    //  PROPERTIES  //

    /** The available settings defaults. */
    const m_defaults: Settings = {
        'server.executablePath': '',
        'server.loggingLevel': Output.Level.WARN,
    };

    //  PUBLIC METHODS  //

    /** Gets the settings title to be used. */
    export const section = () => Product.identifier;

    /** Handles showing the underlying settings. */
    export const open = () =>
        vscode.commands.executeCommand<any>(
            'workbench.action.openSettings',
            `@ext:${Product.identifier}.${Product.identifier}-lang`,
        );

    /** Gets the entire configuration. */
    export const all = (): Readonly<Settings> => {
        return Object.keys(m_defaults).reduce(
            (settings, key) => ({ ...settings, [key]: get(key as keyof Settings) }),
            {} as Settings, // prepare the default set of settings to inherit
        );
    };

    /**
     * Handles getting a settings value.
     * @param key               Key of settings.
     * @param fallback          Optional fallback.
     */
    export const get = <K extends keyof Settings>(key: K, fallback = m_defaults[key]) =>
        m_configuration().get<Settings[K]>(key) ?? fallback;

    /**
     * Listens for a configuration change.
     * @param key               Key that changed.
     * @param callback          Event callback.
     */
    export function listen(callback: (settings: Settings) => any): vscode.Disposable;
    export function listen<K extends keyof Settings>(key: K, callback: (value: Settings[K]) => any): vscode.Disposable;
    export function listen(key: string | Function, callback?: Function): vscode.Disposable {
        if (typeof key === 'string') return m_listenKeyChanged(key as keyof Settings, callback as any);
        else return m_listenAllChanged((callback = key) as any); // otherwise default to all handler
    }

    /** Gets the underlying contribution. */
    export function contribution(): Inversify.Newable<Service> {
        return Service;
    }

    //  PRIVATE METHODS  //

    /** Handles getting the underlying configuration. */
    function m_configuration() {
        return vscode.workspace.getConfiguration(section());
    }

    //  EVENT HANDLERS  //

    /**
     * Handles subscribing to any changes.
     * @param callback              Callback to bind.
     */
    function m_listenAllChanged(callback: (settings: Settings) => any) {
        return vscode.workspace.onDidChangeConfiguration((event) => {
            if (event.affectsConfiguration(section())) callback(all());
        });
    }

    /**
     * Handles subscribing to a key-change.
     * @param key                   Key that changed.
     * @param callback              Callback to bind.
     */
    function m_listenKeyChanged<K extends keyof Settings>(key: K, callback?: (value: Settings[K]) => any) {
        // ignore if the callback is invalid at all
        if (typeof callback === 'undefined') return vscode.Disposable.from();

        // get the original value to be compared against
        let previous = get(key);

        // and subscribe to the incoming configuration changes
        return vscode.workspace.onDidChangeConfiguration((event) => {
            // ignore if the workspace was not affected
            if (!event.affectsConfiguration(section())) return;

            // then we get the incoming value
            const current = get(key);

            // if they are different, then delegate
            if (previous !== current) callback((previous = current));
        });
    }
}
