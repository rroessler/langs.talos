/// VSC Modules
import { Decorator, Dependency, Disposable, Inversify } from '@/vscode/utilities';

/// Package Modules
import { Plugin } from './plugin';
import { Context } from './context';
import { Service } from './service';

/** Extension Lifecycle. */
@Inversify.injectable()
@Decorator.Class.Rename('Extension.Service')
export class Lifecycle extends Disposable implements Service {
    //  PROPERTIES  //

    /** The underlying extension API. */
    @Inversify.inject(Context) protected readonly m_context!: Context;

    /** Extension Plugins Provider. */
    @Dependency.inject(Plugin) protected readonly m_plugins!: Dependency<Plugin>;

    //  LIFECYCLE METHODS  //

    /** Gets the underlying context. */
    context() {
        return this.m_context;
    }

    /** Handles activating the lifecycle. */
    async activate() {
        // pre-push this instance as disposable now
        this.m_context.subscriptions.push(this);

        // configure and activate all the available extension
        const plugins = this.m_plugins.get();

        // attempt configuring and activating the plugins
        await this.m_apply('configure', plugins);
        await this.m_apply('activate', plugins);
    }

    /** Handles disposing of the lifecycle. */
    dispose() {
        for (const plugin of this.m_plugins) plugin.dispose?.();
    }

    //  PRIVATE METHODS  //

    /**
     * Allows measuring the total time plugins take.
     * @param action                    Action to measure.
     * @param plugins                   Plugin contributions.
     */
    private async m_apply<K extends Plugin.Action>(action: K, plugins: readonly Plugin[]) {
        const elapsed = await Promise.all(plugins.map((plugin) => this.m_measure(action, plugin)));
        console.info(`Extension.Service.${action} took ${elapsed.reduce((acc, value) => acc + value, 0)} ms`);
    }

    /**
     * Measures a single plugins action.
     * @param action                    Action to measure.
     * @param plugin                    Plugin instance.
     */
    private async m_measure<K extends Plugin.Action>(action: K, plugin: Plugin): Promise<number> {
        // ensure that we have a valid method
        const method = plugin[action];
        if (typeof method === 'undefined') return 0;

        const start = performance.now();
        await method.call(plugin);
        const elapsed = performance.now() - start;

        // show a log about the performance being taken now
        console.debug(`${plugin.constructor.name}.${action} took ${elapsed} ms`);

        // return the total elapsed time now
        return elapsed;
    }
}
